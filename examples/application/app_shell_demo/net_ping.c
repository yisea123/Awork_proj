#include "lwip/sockets.h"
#include "lwip/icmp.h"
#include "lwip/mem.h"
#include "ipv4/lwip/ip.h"
#include "lwip/dns.h"
#include "lwip/sys.h"

#include "aw_vdebug.h"

#define PING_ID                 (0xAFAF)

#define PING_DATA_MIN_SIZE      (32)      /** ping additional data size to include in the packet */
#define PING_DATA_MAX_SIZE      (1400)

static uint16_t                 __g_ping_seq_num = 0;

/**
 *  Prepare the contents of an echo ICMP request packet
 *
 *  @param iecho  : Pointer to an icmp_echo_hdr structure in which the ICMP packet will be constructed
 *  @param len    : The length in bytes of the packet buffer passed to the iecho parameter
 *
 */

static void ping_prepare_echo( struct icmp_echo_hdr *iecho, uint16_t len )
{
    int i;

    ICMPH_TYPE_SET( iecho, ICMP_ECHO );
    ICMPH_CODE_SET( iecho, 0 );
    iecho->chksum = 0;
    iecho->id = PING_ID;
    iecho->seqno = htons( ++__g_ping_seq_num );

    /* fill the additional data buffer with some data */
    for ( i = 0; i < len; i++ ) {
        ( (char*) iecho )[sizeof(struct icmp_echo_hdr) + i] = i;
    }

    iecho->chksum = inet_chksum( iecho, len + sizeof(struct icmp_echo_hdr) );
}



/**
 *  Send a Ping
 *
 *  Sends a ICMP echo request (Ping) to the specified IP address, using the specified socket.
 *
 *  @param socket_hnd : The handle for the local socket through which the ping request will be sent
 *  @param addr       : The IP address to which the ping request will be sent
 *
 *  @return  ERR_OK if successfully sent, ERR_MEM if out of memory or ERR_VAL otherwise
 */

static err_t ping_send( int socket_hnd, struct in_addr *addr, int ping_size )
{
    int err, bs;
    struct icmp_echo_hdr *iecho;
    struct sockaddr_in to;

    bs = ping_size + sizeof(struct icmp_echo_hdr);
    /* Allocate memory for packet */
    if ( !( iecho = (struct icmp_echo_hdr*) mem_malloc( bs ) )) {
        return ERR_MEM;
    }

    /* Construct ping request */
    ping_prepare_echo( iecho, ping_size );

    /* Send the ping request */
    to.sin_len = sizeof( to );
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = addr->s_addr;

    err = lwip_sendto( socket_hnd, iecho, bs, 0, (struct sockaddr*) &to, sizeof( to ) );

    /* free packet */
    mem_free( iecho );

    return ( err ? ERR_OK : ERR_VAL );
}


/**
 *  Receive a Ping reply
 *
 *  Waits for a ICMP echo reply (Ping reply) to be received using the specified socket. Compares the
 *  sequence number, and ID number to the last ping sent, and if they match, returns ERR_OK, indicating
 *  a valid ping response.
 *
 *  @param socket_hnd : The handle for the local socket through which the ping reply will be received
 *
 *  @return  ERR_OK if valid reply received, ERR_TIMEOUT otherwise
 */

static err_t ping_recv( int socket_hnd , int ping_size)
{
    char *recv_buf;
    size_t buf_size = 0;
    int fromlen, len;
    struct sockaddr_in from;
    struct ip_hdr *iphdr;
    struct icmp_echo_hdr *iecho;

    buf_size = ping_size + (int) ( sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr) );
    recv_buf = mem_malloc( buf_size );

    while ( ( len = lwip_recvfrom( socket_hnd, recv_buf, buf_size, 0, (struct sockaddr*) &from, (socklen_t*) &fromlen ) ) > 0 )
    {
        if ( len >= (int) ( sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr) ) )
        {
            iphdr = (struct ip_hdr *) recv_buf;
            iecho = (struct icmp_echo_hdr *) ( recv_buf + ( IPH_HL( iphdr ) * 4 ) );

            if ( ( iecho->id == PING_ID ) &&
                 ( iecho->seqno == htons( __g_ping_seq_num ) ) &&
                 ( ICMPH_TYPE( iecho ) == ICMP_ER ) )
            {
                mem_free( recv_buf );
                return ERR_OK; /* Echo reply received - return success */
            }
        }
    }

    mem_free( recv_buf );
    return ERR_TIMEOUT; /* No valid echo reply received before timeout */
}

/**
 * \brief ping function
 *
 * \param   p_nic_name  NIC name, if p_nic_name = NULL, the NIC is automatically selected.
 * \param   dst_addr    destination IP address or domain name
 * \param   ping_size   ping send data size. should be between PING_DATA_MIN_SIZE and PING_DATA_MAX_SIZE
 * \param   timout_ms   ping receive timeout - in milliseconds
 *
 * \retval  -AW_EPERM   ping_size should be between PING_DATA_MIN_SIZE and PING_DATA_MAX_SIZE
 * \retval  -AW_ENOSR   socket alloc failed
 * \retval  -AW_EAGAIN  send data failed
 * \retval  -AW_ETIME   timeout
 * \retval  >0          time in milliseconds
 */
int net_ping (struct in_addr ipaddr, int ping_size, int timout_ms)
{
    int   socket_hnd;
    int   recv_timeout = timout_ms;
    err_t err;
    int   timo = -AW_ENOSR;

    uint32_t timenow;

    if (ping_size < PING_DATA_MIN_SIZE || ping_size > PING_DATA_MAX_SIZE) {
        return -AW_EPERM;
    }

    /* Open a local socket for pinging */
    if ( ( socket_hnd = lwip_socket( AF_INET, SOCK_RAW, IP_PROTO_ICMP ) ) < 0 ) {
        AW_ERRF(( "unable to create socket for Ping\n" ));
        return -AW_ENOSR;
    }

    /* Set the receive timeout on local socket so pings will time out. */
    lwip_setsockopt( socket_hnd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof( recv_timeout ) );

    /* Send a ping */
    if ( ping_send( socket_hnd, &ipaddr, ping_size ) != ERR_OK ) {
        AW_ERRF(( "Unable to send Ping\n" ));
        timo = -AW_EAGAIN;
        goto __exit;
    }
    timenow = sys_now();

    err = ping_recv( socket_hnd, ping_size );
    if ( ERR_OK == err ) {
        timo = sys_now() - timenow;
        goto __exit;
    } else {
        timo = -AW_ETIME;
        goto __exit;
    }

__exit:
    lwip_close(socket_hnd);
    return timo;
}

/* end of file */

