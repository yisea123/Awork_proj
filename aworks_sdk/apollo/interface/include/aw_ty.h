/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief TTY����֧��ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-20  deo, add aw_tydev_remove
 * - 1.02 12-12-08  orz, change type of size and nbytes to size_t.
 * - 1.00 12-10-19  orz, created
 * \endinternal
 */

#ifndef __AW_TY_H
#define __AW_TY_H

/*
 * \addtogroup grp_aw_ty
 * @{
 */

/*lint ++flb */

#include "aw_common.h"
#include "aw_rngbuf.h"
#include "aw_spinlock.h"
#include "aw_sem.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/**
 * \name serial ioctl option values
 * @{
 */

#define AW_OPT_ECHO     0x01    /**< \brief echo input */
#define AW_OPT_CRMOD    0x02    /**< \brief lf -> crlf */
#define AW_OPT_TANDEM   0x04    /**< \brief ^S/^Q flow control protocol */
#define AW_OPT_7_BIT    0x08    /**< \brief strip parity bit from 8 bit input */
#define AW_OPT_MON_TRAP 0x10    /**< \brief enable trap to monitor */
#define AW_OPT_ABORT    0x20    /**< \brief enable shell restart */
#define AW_OPT_LINE     0x40    /**< \brief enable basic line protocol */

#define AW_OPT_RAW      0       /**< \brief raw mode */

/** \brief terminal mode */
#define AW_OPT_TERMINAL     (AW_OPT_ECHO | AW_OPT_CRMOD | AW_OPT_TANDEM | \
                             AW_OPT_MON_TRAP | AW_OPT_7_BIT | AW_OPT_ABORT | AW_OPT_LINE)
/** @} */

/******************************************************************************/

/**
 * \name tty driver configurations
 * @{
 */
#define AW_CONFIG_SERIAL_SOFT_FLOW_CTRL /**< \brief ʹ��������ģ�� */
#define AW_CONFIG_SERIAL_THRESHOLD      /**< \brief ʹ������Ĭ���շ���ֵ */
#define AW_CONFIG_SERIAL_LINE_MODE      /**< \brief ʹ���ж�дģʽ */
#define AW_CONFIG_SERIAL_PROTO_HOOK     /**< \brief ʹ��Э��ص��ӿ� */
#define AW_CONFIG_SERIAL_SYNC           /**< \brief ʹ��ͬ������ */

#if 0
#define AW_CONFIG_SERIAL_FLOW_CTRL_TRACE/**< \brief ʹ�����ظ��� */
#define AW_CONFIG_SERIAL_CANCELE        /**< \brief ʹ��֧��ȡ������ */
#define AW_CONFIG_SERIAL_SELECT         /**< \brief ʹ��select֧�� */
#endif

#ifdef AW_CONFIG_SERIAL_LINE_MODE
#undef  MAX_INPUT
#define MAX_INPUT   64
#endif
/** @} */

/******************************************************************************/

/** \brief tty�豸�����ṹ */
struct aw_tydev {
    struct aw_rngbuf  rdbuf;            /**< \brief �����ݻ��λ��� */
    struct aw_rngbuf  wrbuf;            /**< \brief д���ݻ��λ��� */

    AW_MUTEX_DECL(mutex_sem);           /**< \brief �豸�����ź��� */
#ifdef AW_CONFIG_SERIAL_SYNC
    int          rd_timeout;            /**< \brief �����ݳ�ʱʱ�� */
    AW_SEMB_DECL(rdsync_sem);           /**< \brief ��ͬ���ź��� */
    AW_SEMB_DECL(wrsync_sem);           /**< \brief дͬ���ź��� */
#endif

    /** \brief ��ͨ����ǰ״̬ */
    struct {
#ifdef AW_CONFIG_SERIAL_CANCELE
        unsigned char canceled;         /**< \brief �������Ѿ�ȡ�� */
#endif
#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
        unsigned char xoff;             /**< \brief �����Ѿ���XOFF�ص��� */
        unsigned char pending;          /**< \brief XON/XOFF���ڿ���ʱ���� */
#endif
        unsigned char flushing_rdbuf;   /**< \brief ���������ٽ��־ */
    } rdstate;

    /** \brief дͨ��״̬ */
    struct {
#ifdef AW_CONFIG_SERIAL_CANCELE
        unsigned char canceled;         /**< \brief д�����Ѿ�ȡ�� */
#endif
        unsigned char busy;             /**< \brief дͨ���Ƿ�æ�������У� */
#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
        unsigned char xoff;             /**< \brief ����Ѿ���XOFF�ص��� */
#endif
#ifdef AW_CONFIG_SERIAL_LINE_MODE
        unsigned char cr;               /**< \brief �Ƿ���Ҫ����س��� */
#endif
        unsigned char flushing_wrbuf;   /**< \brief ��д�����ٽ��־ */
        unsigned char wrbuf_busy;       /**< \brief ��������������д���� */
    } wrstate;

#ifdef AW_CONFIG_SERIAL_LINE_MODE
    unsigned char   ln_nbytes;          /**< \brief δ������������ֽ��� */
    unsigned char   ln_bytes_left;      /**< \brief ûȫ��ȡ�ߵ�����ʣ���ֽ���*/
#endif

    unsigned short  options;            /**< \brief �豸��Ϊ���� */

    /** \brief �������͵ĺ���ָ�� */
    void (*pfunc_tx_start)(struct aw_tydev *p_tydev);

#ifdef AW_CONFIG_SERIAL_PROTO_HOOK
    /**
     * \brief Э��ص����Ӻ���
     *
     * ������Ӻ����ڴ����豸ÿ�յ�һ���ַ�ʱ�ص������ڸ��ִ���Э���ʵ�֣�
     * ��Modbus
     *
     * \param p_arg �ص�����
     * \param ch    ���յ����ַ�
     *
     * \return      ���Э�鲻��Ҫ��������\a ch �򷵻�1�����򷵻�0
     */
    int  (*pfunc_proto_hook)(void *p_arg, char ch);
    /** \brief Э��ص����� */
    void  *p_proto_arg;
#endif

#ifdef AW_CONFIG_SERIAL_SELECT
    /** \brief ����select������������豸�ϵ��߳����� */
    AW_SEL_WKUP_LIST_DECLARE(sel_wkup_list);
    /** \brief �豸�򿪼����� */
    int num_open; /* todo: ʹ��ԭ�����ͣ� */
#endif

    int wr_threshold;       /**< \brief �������������߷��͵ķ��ͻ�����ֵ */

#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
    int xoff_threshold;     /**< \brief ����XOFF�Ľ��ջ�����ֵ */
    int xon_threshold;      /**< \brief ����XON�Ľ��ջ�����ֵ */
    /**
     * \brief �豸���XOFF/XON�ص�
     * \param p_arg �ص�����
     * \param xoff  ��ǰ���͵���XOFF(1)����XON(0)
     */
    void  (*pfunc_xoff_hook)(void *p_arg, int xoff);
    /** \brief �豸���XOFF/XON�ص����� */
    void   *p_xoff_arg;
#endif

#if 0
    int     flags;  /**< \brief �豸��־ */
#endif

    aw_spinlock_isr_t   spinlock_isr; /**< \brief �����ж���ʹ�õ�spinlock */
};

aw_err_t aw_tylib_init (int xoff_percent, int xon_percent, int wr_threshold);

aw_err_t aw_tydev_init (struct aw_tydev *p_tydev,
                        char            *rd_buf,
                        size_t           rd_buf_size,
                        char            *wr_buf,
                        size_t           wr_buf_size,
                        void           (*pfunc_tx_start)(struct aw_tydev *));
aw_err_t aw_tydev_remove (struct aw_tydev *p_tydev);

aw_err_t aw_ty_int_tx (struct aw_tydev *p_tydev, char *p_char);
aw_err_t aw_ty_int_rd (struct aw_tydev *p_tydev, char inchar);

aw_err_t aw_ty_ioctl (struct aw_tydev *p_tydev, int request, void *p_arg);

ssize_t aw_ty_write(struct aw_tydev *p_tydev, const char *p_buf, size_t nbytes);
ssize_t aw_ty_read (struct aw_tydev *p_tydev, char *p_buf, size_t maxbytes);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AW_TY_H */

/* end of file */
