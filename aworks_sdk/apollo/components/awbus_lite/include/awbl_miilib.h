/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief MII library
 *
 * \internal
 * \par modification history
 * - 1.00 15-04-23  axn, first implementation (from vxWorks)
 * \endinternal
 */
#ifndef __AWBL_MIILIB_H
#define __AWBL_MIILIB_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus 	*/


/* MII definitions */
#define AWBL_MII_CRC_LEN				0x4	/* CRC length in bytes */
//#define AWBL_MII_ETH_MAX_PCK_SZ      	(ETHERMTU + SIZEOF_ETHERHEADER + AWBL_MII_CRC_LEN)
#define AWBL_MII_MAX_PHY_NUM			0x20	/* max number of attached PHYs */
#define AWBL_MII_MAX_REG_NUM         	0x20    /* max number of registers */

#define AWBL_MII_CTRL_REG				0x0	/* Control Register */
#define AWBL_MII_STAT_REG				0x1	/* Status Register */
#define AWBL_MII_PHY_ID1_REG			0x2	/* PHY identifier 1 Register */
#define AWBL_MII_PHY_ID2_REG			0x3	/* PHY identifier 2 Register */
#define AWBL_MII_AN_ADS_REG				0x4	/* Auto-Negotiation 	  */
											/* Advertisement Register */
#define AWBL_MII_AN_PRTN_REG			0x5	/* Auto-Negotiation 	    */
											/* partner ability Register */
#define AWBL_MII_AN_EXP_REG				0x6	/* Auto-Negotiation   */
											/* Expansion Register */
#define AWBL_MII_AN_NEXT_REG			0x7	/* Auto-Negotiation 	       */
											/* next-page transmit Register */

#define AWBL_MII_AN_PRTN_NEXT_REG		0x8  /* Link partner received next page */
#define AWBL_MII_MASSLA_CTRL_REG		0x9  /* MATER-SLAVE control register */
#define AWBL_MII_MASSLA_STAT_REG		0xa  /* MATER-SLAVE status register */
#define AWBL_MII_EXT_STAT_REG			0xf  /* Extented status register */


/* MII control register bit  */
#define AWBL_MII_CR_1000		    	0x0040	/* 1 = 1000mb when AWBL_MII_CR_100 is also 1 */
#define AWBL_MII_CR_COLL_TEST			0x0080	/* collision test */
#define AWBL_MII_CR_FDX		    		0x0100	/* FDX =1, half duplex =0 */
#define AWBL_MII_CR_RESTART				0x0200	/* restart auto negotiation */
#define AWBL_MII_CR_ISOLATE				0x0400	/* isolate PHY from MII */
#define AWBL_MII_CR_POWER_DOWN			0x0800	/* power down */
#define AWBL_MII_CR_AUTO_EN				0x1000	/* auto-negotiation enable */
#define AWBL_MII_CR_100		    		0x2000	/* 0 = 10mb, 1 = 100mb */
#define AWBL_MII_CR_LOOPBACK			0x4000	/* 0 = normal, 1 = loopback */
#define AWBL_MII_CR_RESET				0x8000	/* 0 = normal, 1 = PHY reset */
#define AWBL_MII_CR_NORM_EN				0x0000	/* just enable the PHY */
#define AWBL_MII_CR_DEF_0_MASK       	0xca7f  /* they must return zero */
#define AWBL_MII_CR_RES_MASK       		0x003f  /* reserved bits,return zero */


/* MII Status register bit definitions */

#define AWBL_MII_SR_LINK_STATUS			0x0004	/* link Status -- 1 = link */
#define AWBL_MII_SR_AUTO_SEL			0x0008  /* auto speed select capable */
#define AWBL_MII_SR_REMOTE_FAULT     	0x0010  /* Remote fault detect */
#define AWBL_MII_SR_AUTO_NEG         	0x0020  /* auto negotiation complete */
#define AWBL_MII_SR_EXT_STS				0x0100	/* extended sts in reg 15 */
#define AWBL_MII_SR_T2_HALF_DPX			0x0200	/* 100baseT2 HD capable */
#define AWBL_MII_SR_T2_FULL_DPX			0x0400	/* 100baseT2 FD capable */
#define AWBL_MII_SR_10T_HALF_DPX     	0x0800  /* 10BaseT HD capable */
#define AWBL_MII_SR_10T_FULL_DPX     	0x1000  /* 10BaseT FD capable */
#define AWBL_MII_SR_TX_HALF_DPX      	0x2000  /* TX HD capable */
#define AWBL_MII_SR_TX_FULL_DPX      	0x4000  /* TX FD capable */
#define AWBL_MII_SR_T4               	0x8000  /* T4 capable */
#define AWBL_MII_SR_ABIL_MASK        	0xff80  /* abilities mask */
#define AWBL_MII_SR_EXT_CAP          	0x0001  /* extended capabilities */
#define AWBL_MII_SR_SPEED_SEL_MASK 		0xf800  /* Mask to extract just speed
                                                 * capabilities  from status
                                                 * register.
                                                 */
/*  MII ID2 register bit mask */

#define AWBL_MII_ID2_REVISON_MASK    	0x000f
#define AWBL_MII_ID2_MODE_MASK       	0x03f0

/* MII AN advertisement Register bit definition */

#define AWBL_MII_ANAR_10TX_HD        	0x0020
#define AWBL_MII_ANAR_10TX_FD        	0x0040
#define AWBL_MII_ANAR_100TX_HD       	0x0080
#define AWBL_MII_ANAR_100TX_FD       	0x0100
#define AWBL_MII_ANAR_100T_4         	0x0200
#define AWBL_MII_ANAR_PAUSE          	0x0400
#define AWBL_MII_ANAR_ASM_PAUSE      	0x0800
#define AWBL_MII_ANAR_REMORT_FAULT   	0x2000
#define AWBL_MII_ANAR_NEXT_PAGE      	0x8000
#define AWBL_MII_ANAR_PAUSE_MASK     	0x0c00

/* MII Link Code word  bit definitions */

#define AWBL_MII_BP_FAULT				0x2000	/* remote fault */
#define AWBL_MII_BP_ACK					0x4000	/* acknowledge */
#define AWBL_MII_BP_NP					0x8000	/* nexp page is supported */

/* MII Next Page bit definitions */

#define AWBL_MII_NP_TOGGLE				0x0800	/* toggle bit */
#define AWBL_MII_NP_ACK2				0x1000	/* acknowledge two */
#define AWBL_MII_NP_MSG					0x2000 	/* message page */
#define AWBL_MII_NP_ACK1				0x4000 	/* acknowledge one */
#define AWBL_MII_NP_NP					0x8000 	/* nexp page will follow */

/* MII Expansion Register bit definitions */

#define AWBL_MII_EXP_FAULT				0x0010	/* parallel detection fault */
#define AWBL_MII_EXP_PRTN_NP			0x0008 	/* link partner next-page able */
#define AWBL_MII_EXP_LOC_NP				0x0004	/* local PHY next-page able */
#define AWBL_MII_EXP_PR					0x0002	/* full page received */
#define AWBL_MII_EXP_PRT_AN				0x0001 	/* link partner auto negotiation able */

/* MII Master-Slave Control register bit definition */

#define AWBL_MII_MASSLA_CTRL_1000T_HD	0x100
#define AWBL_MII_MASSLA_CTRL_1000T_FD	0x200
#define AWBL_MII_MASSLA_CTRL_PORT_TYPE	0x400
#define AWBL_MII_MASSLA_CTRL_CONFIG_VAL	0x800
#define AWBL_MII_MASSLA_CTRL_CONFIG_EN	0x1000

/* MII Master-Slave Status register bit definition */

#define AWBL_MII_MASSLA_STAT_LP1000T_HD	0x400
#define AWBL_MII_MASSLA_STAT_LP1000T_FD	0x800
#define AWBL_MII_MASSLA_STAT_REMOTE_RCV	0x1000
#define AWBL_MII_MASSLA_STAT_LOCAL_RCV	0x2000
#define AWBL_MII_MASSLA_STAT_CONF_RES	0x4000
#define AWBL_MII_MASSLA_STAT_CONF_FAULT	0x8000

/* MII Extented Status register bit definition */

#define AWBL_MII_EXT_STAT_1000T_HD		0x1000
#define AWBL_MII_EXT_STAT_1000T_FD		0x2000
#define AWBL_MII_EXT_STAT_1000X_HD		0x4000
#define AWBL_MII_EXT_STAT_1000X_FD		0x8000

/* technology ability field bit definitions */

#define AWBL_MII_TECH_10BASE_T			0x0020	/* 10Base-T */
#define AWBL_MII_TECH_10BASE_FD			0x0040	/* 10Base-T Full Duplex */
#define AWBL_MII_TECH_100BASE_TX		0x0080	/* 100Base-TX */
#define AWBL_MII_TECH_100BASE_TX_FD		0x0100	/* 100Base-TX Full Duplex */
#define AWBL_MII_TECH_100BASE_T4		0x0200	/* 100Base-T4 */

#define AWBL_MII_TECH_PAUSE				0x0400  /* PAUSE */
#define AWBL_MII_TECH_ASM_PAUSE			0x0800  /* Asym pause */
#define AWBL_MII_TECH_PAUSE_MASK		0x0c00

#define AWBL_MII_ADS_TECH_MASK			0x1fe0	/* technology abilities mask */
#define AWBL_MII_TECH_MASK				AWBL_MII_ADS_TECH_MASK
#define AWBL_MII_ADS_SEL_MASK			0x001f	/* selector field mask */

#define AWBL_MII_AN_FAIL             	0x10    /* auto-negotiation fail */
#define AWBL_MII_STAT_FAIL           	0x20    /* errors in the status register */
#define AWBL_MII_PHY_NO_ABLE     		0x40    /* the PHY lacks some abilities */

/* MII management frame structure */

#define AWBL_MII_MF_PREAMBLE			0xffffffff	/* preamble pattern */
#define AWBL_MII_MF_ST					0x1		/* start of frame pattern */
#define AWBL_MII_MF_OP_RD				0x2		/* read operation pattern */
#define AWBL_MII_MF_OP_WR				0x1		/* write operation pattern */

#define AWBL_MII_MF_PREAMBLE_LEN		0x20	/* preamble lenght in bit */
#define AWBL_MII_MF_ST_LEN				0x2		/* start frame lenght in bit */
#define AWBL_MII_MF_OP_LEN				0x2		/* op code lenght in bit */
#define AWBL_MII_MF_ADDR_LEN			0x5		/* PHY addr lenght in bit */
#define AWBL_MII_MF_REG_LEN				0x5		/* PHY reg lenght in bit */
#define AWBL_MII_MF_TA_LEN				0x2		/* turnaround lenght in bit */
#define AWBL_MII_MF_DATA_LEN			0x10	/* data lenght in bit */

/* defines related to the PHY device */

#define AWBL_MII_PHY_PRE_INIT    		0x0001	/* PHY info pre-initialized */
#define AWBL_MII_PHY_AUTO        		0x0010	/* auto-negotiation allowed */
#define AWBL_MII_PHY_TBL         		0x0020	/* use negotiation table */
#define AWBL_MII_PHY_100         		0x0040 	/* PHY may use 100Mbit speed */
#define AWBL_MII_PHY_10          		0x0080 	/* PHY may use 10Mbit speed */
#define AWBL_MII_PHY_FD          		0x0100 	/* PHY may use full duplex */
#define AWBL_MII_PHY_HD          		0x0200 	/* PHY may use half duplex */
#define AWBL_MII_PHY_ISO				0x0400	/* isolate all PHYs */
#define AWBL_MII_PHY_PWR_DOWN    		0x0800	/* power down mode */
#define AWBL_MII_PHY_DEF_SET			0x1000	/* set a default mode */
#define AWBL_MII_ALL_BUS_SCAN			0x2000	/* scan the all bus */
#define AWBL_MII_PHY_MONITOR			0x4000	/* monitor the PHY's status */
#define AWBL_MII_PHY_INIT				0x8000	/* PHY info initialized */
#define AWBL_MII_PHY_1000T_FD			0x10000	/* PHY may use 1000-T full duplex */
#define AWBL_MII_PHY_1000T_HD			0x20000	/* PHY mau use 1000-T half duplex */
#define AWBL_MII_PHY_TX_FLOW_CTRL		0x40000	/* Transmit flow control */
#define AWBL_MII_PHY_RX_FLOW_CTRL		0x80000	/* Receive flow control */
#define AWBL_MII_PHY_GMII_TYPE			0x100000 /* GMII = 1, MII = 0 */
#define AWBL_MII_PHY_ISO_UNAVAIL		0x200000 /* ctrl reg isolate func not available */

/* miscellaneous defines */

#define AWBL_MII_PHY_DEF_DELAY   		300		/* max delay before link up, etc. */
#define AWBL_MII_PHY_NO_DELAY    		0x0		/* do not delay */
#define AWBL_MII_PHY_NULL        		0xff	/* PHY is not present */
#define AWBL_MII_PHY_DEF_ADDR    		0x0		/* default PHY's logical address */

#ifndef AWBL_MII_MONITOR_DELAY
	#define AWBL_MII_MONITOR_DELAY   	0x2		/* in seconds */
#endif

#define AWBL_MII_PHY_LINK_UNKNOWN		0x0		/* link method - Unknown */
#define AWBL_MII_PHY_LINK_AUTO	0x1       /* link method - Auto-Negotiation */
#define AWBL_MII_PHY_LINK_FORCE	0x2       /* link method - Force link */

/*
 * these values may be used in the default phy mode field of the load
 * string, since that is used to force the operating mode of the PHY
 * in case any attempt to establish the link failed.
 */

#define AWBL_PHY_10BASE_T            	0x00     /* 10 Base-T */
#define AWBL_PHY_10BASE_T_FDX        	0x01     /* 10 Base Tx, full duplex */
#define AWBL_PHY_100BASE_TX          	0x02     /* 100 Base Tx */
#define AWBL_PHY_100BASE_TX_FDX      	0x03     /* 100 Base TX, full duplex */
#define AWBL_PHY_100BASE_T4          	0x04     /* 100 Base T4 */
#define AWBL_PHY_AN_ENABLE          	0x05     /* re-enable auto-negotiation */

#define AWBL_MII_FDX_STR         		"full duplex"   /* full duplex mode */
#define AWBL_MII_FDX_LEN         		sizeof (AWBL_MII_FDX_STR)   /* full duplex mode */
#define AWBL_MII_HDX_STR         		"half duplex"   /* half duplex mode */
#define AWBL_MII_HDX_LEN         		sizeof (AWBL_MII_HDX_STR)   /* full duplex mode */

#define AWBL_MII_AN_TBL_MAX				20	/* max number of entries in the table */

/* allowed PHY's speeds */
#define AWBL_MII_1000MBS         		1000000000      /* bits per sec */
#define AWBL_MII_100MBS          		100000000       /* bits per sec */
#define AWBL_MII_10MBS           		10000000        /* bits per sec */

/*
 * if_media Options word:
 *	Bits	Use
 *	----	-------
 *	0-4	Media variant
 *	5-7	Media type
 *	8-15	Type specific options
 *	16-18	Mode (for multi-mode devices)
 *	19	RFU
 *	20-27	Shared (global) options
 *	28-31	Instance
 */

/*
 * Ethernet
 */
#define	AWBL_IFM_ETHER			0x00000020
#define	AWBL_IFM_10_T			3		/* 10BaseT - RJ45 */
#define	AWBL_IFM_10_2			4		/* 10Base2 - Thinnet */
#define	AWBL_IFM_10_5			5		/* 10Base5 - AUI */
#define	AWBL_IFM_100_TX			6		/* 100BaseTX - RJ45 */
#define	AWBL_IFM_100_FX			7		/* 100BaseFX - Fiber */
#define	AWBL_IFM_100_T4			8		/* 100BaseT4 - 4 pair cat 3 */
#define	AWBL_IFM_100_VG			9		/* 100VG-AnyLAN */
#define	AWBL_IFM_100_T2			10		/* 100BaseT2 */
#define	AWBL_IFM_1000_SX		11		/* 1000BaseSX - multi-mode fiber */
#define	AWBL_IFM_10_STP			12		/* 10BaseT over shielded TP */
#define	AWBL_IFM_10_FL			13		/* 10BaseFL - Fiber */
#define	AWBL_IFM_1000_LX		14		/* 1000baseLX - single-mode fiber */
#define	AWBL_IFM_1000_CX		15		/* 1000baseCX - 150ohm STP */
#define	AWBL_IFM_1000_T			16		/* 1000baseT - 4 pair cat 5 */
#define	AWBL_IFM_HPNA_1			17		/* HomePNA 1.0 (1Mb/s) */
#define AWBL_IFM_10G_LR			18		/* 10GBase-LR 1310nm Single-mode */
#define AWBL_IFM_10G_SR			19		/* 10GBase-SR 850nm Multi-mode */
#define AWBL_IFM_10G_CX4		20		/* 10GBase CX4 copper */
#define AWBL_IFM_2500_SX    	21              /* 2500BaseSX - multi-mode fiber */
#define AWBL_IFM_10G_TWINAX		22		/* 10GBase Twinax copper */
#define AWBL_IFM_10G_TWINAX_LONG 2		/* 10GBase Twinax Long copper */
#define AWBL_IFM_10G_LRM		24		/* 10GBase-LRM 850nm Multi-mode */
#define AWBL_IFM_UNKNOWN		25		/* New media types that have not been defined yet */
#define AWBL_IFM_10G_T			26		/* 10GBase-T */


/*
 * Shared media sub-types
 */
#define	AWBL_IFM_AUTO			0		/* Autoselect best media */
#define	AWBL_IFM_MANUAL			1		/* Jumper/dipswitch selects media */
#define	AWBL_IFM_NONE			2		/* Deselect all media */

/*
 * Shared options
 */
#define	AWBL_IFM_FDX			0x00100000	/* Force full duplex */
#define	AWBL_IFM_HDX			0x00200000	/* Force half duplex */
#define	AWBL_IFM_FLAG0			0x01000000	/* Driver defined flag */
#define	AWBL_IFM_FLAG1			0x02000000	/* Driver defined flag */
#define	AWBL_IFM_FLAG2			0x04000000	/* Driver defined flag */
#define	AWBL_IFM_LOOP			0x08000000	/* Put hardware in loopback */

/*
 * Masks
 */
#define	AWBL_IFM_NMASK			0x000000e0	/* Network type */
#define	AWBL_IFM_TMASK			0x0000001f	/* Media sub-type */
#define	AWBL_IFM_IMASK			0xf0000000	/* Instance */
#define	AWBL_IFM_ISHIFT			28		    /* Instance shift */
#define	AWBL_IFM_OMASK			0x0000ff00	/* Type specific options */
#define	AWBL_IFM_MMASK			0x00070000	/* Mode */
#define	AWBL_IFM_MSHIFT			16		    /* Mode shift */
#define	AWBL_IFM_GMASK			0x0ff00000	/* Global options */

/*
 * Status bits
 */
#define	AWBL_IFM_AVALID			0x00000001	/* Active bit valid */
#define	AWBL_IFM_ACTIVE			0x00000002	/* Interface attached to working net */

/*
 * Macros to extract various bits of information from the media word.
 */
#define	AWBL_IFM_TYPE(x)         ((x) & AWBL_IFM_NMASK)
#define	AWBL_IFM_SUBTYPE(x)      ((x) & AWBL_IFM_TMASK)
#define	AWBL_IFM_TYPE_OPTIONS(x) ((x) & AWBL_IFM_OMASK)
#define	AWBL_IFM_INST(x)         (((x) & AWBL_IFM_IMASK) >> AWBL_IFM_ISHIFT)
#define	AWBL_IFM_OPTIONS(x)		 ((x) & (AWBL_IFM_OMASK|AWBL_IFM_GMASK))
#define	AWBL_IFM_MODE(x)	     ((x) & AWBL_IFM_MMASK)

#define	AWBL_IFM_INST_MAX		AWBL_IFM_INST(AWBL_IFM_IMASK)

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AWBL_MIILIB_H */
