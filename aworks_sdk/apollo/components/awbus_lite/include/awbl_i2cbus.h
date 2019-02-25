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
 * \brief AWBus I2C���߽ӿ�ͷ�ļ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "awbl_i2cbus.h"
 * \endcode
 * ��ģ��Ϊ I2C ���ߵľ����ʵ��
 *
 * �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-10  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_I2CBUS_H
#define __AWBL_I2CBUS_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_list.h"
#include "aw_i2c.h"         /* ͨ��I2C�ӿ��ļ� */
#include "aw_sem.h"
#include "aw_spinlock.h"

/** \brief ���õȴ� */
#define AWBL_I2C_WAITFOREVER    (AW_SEM_WAIT_FOREVER)

/** \biref �õ�I2C�ӻ��豸�ĸ������� */
#define AWBL_I2C_PARENT_GET(p_dev) \
    ((struct awbl_i2c_master *) \
        (((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))

/** \biref �õ�I2C�ӻ��豸�ĸ���������� */
#define AWBL_I2C_PARENT_BUSID_GET(p_dev) \
        (((struct awbl_i2c_master_devinfo *) \
            AWBL_DEVINFO_GET( \
                ((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))->bus_index)

struct awbl_i2c_master;

/** \biref AWBus I2C ���߿����� (I2C ����) �豸��Ϣ (ƽ̨���ò���) */
struct awbl_i2c_master_devinfo {

    /** \brief ����������Ӧ�����߱�� */
    uint8_t     bus_index;

    /** \brief �����������ٶ� */
    uint32_t    speed;

    /** \brief ��ʱ, ��λ ms�����õȴ��� #AWBL_I2C_WAITFOREVER */
    int          timeout;
};


/** \biref AWBus I2C ���߿����� (I2C ����) �豸��Ϣ (�������ò���) */
struct awbl_i2c_master_devinfo2 {

    uint16_t    features;       /**< ������������(֧�ֵĴ�����Ʊ�־)  */

    /** \brief �������� */
    aw_err_t (*pfunc_xfer_startup)(struct awbl_i2c_master *p_master);
};

/** \biref I2C bus �ӻ��豸����ע����Ϣ�ṹ�� */
typedef struct awbl_i2c_drvinfo {
    struct awbl_drvinfo super;  /**< \brief �̳��� AWBus �豸������Ϣ */
} awbl_i2c_drvinfo_t;

/** \brief AWBus I2C �����豸 (I2C�ӻ�) ʵ�� */
struct awbl_i2c_device {
    struct awbl_dev super;      /**< \brief �̳��� AWBus �豸 */
};

/** \brief AWBus I2C ���߿����� (I2C����) ʵ�� */
struct awbl_i2c_master {
    struct awbl_busctlr super;      /**< \brief �̳��� AWBus ���߿����� */
    struct awbl_i2c_master *p_next; /**< \brief ָ����һ�� I2C ������ */


    /** \brief I2C �����������Ϣ (�������ò���) */
    const struct awbl_i2c_master_devinfo2 *p_devinfo2;

    /** \brief �豸�� */
    aw_spinlock_isr_t lock_dev;

    /** \brief I2C ��������Ϣ���� */
    struct aw_list_head msg_list;

    /** \brief �豸������ */
    AW_MUTEX_DECL(dev_mux);

    /** \brief ��Ϣ�ڴ���� (aw_i2c_read() �Ⱥ���ʹ�ô��ڴ�) */
    struct aw_i2c_message msg;

    /** \brief �����ڴ���� (aw_i2c_read() �Ⱥ���ʹ�ô��ڴ�) */
    struct aw_i2c_transfer trans[2];

    /** \brief �ӵ�ַ�ڴ���� (aw_i2c_read() �Ⱥ���ʹ�ô��ڴ�) */
    uint8_t subaddr[4];
};

/** \brief ���������� */
#define AWBL_I2C_MASTER_LOCK(p_master) \
    aw_spinlock_isr_take(&((struct awbl_i2c_master *)p_master)->lock_dev)

/** \brief ������������� */
#define AWBL_I2C_MASTER_UNLOCK(p_master) \
    aw_spinlock_isr_give(&((struct awbl_i2c_master *)p_master)->lock_dev)

/**
 * \brief ���һ�� message �������������б�ĩβ
 * \attention ���ô˺�����������������
 */
aw_local aw_inline void awbl_i2c_msg_in (struct awbl_i2c_master *p_master,
                                         struct aw_i2c_message *p_msg)
{
    aw_list_add_tail((struct aw_list_head *)(&p_msg->ctlrdata),
                     &p_master->msg_list);
}

/**
 * \brief �ӿ����������б��ͷȡ��һ�� message
 * \attention ���ô˺�����������������
 */
aw_local aw_inline struct aw_i2c_message *
    awbl_i2c_msg_out (struct awbl_i2c_master *p_master)
{
    if (aw_list_empty_careful(&p_master->msg_list)) {
        return NULL;
    } else {
        struct aw_list_head *p_node = p_master->msg_list.next;
        aw_list_del(p_node);
        return aw_list_entry(p_node, struct aw_i2c_message, ctlrdata);
    }
}

/**
 * \brief ȡ��ָ���� message (�Ӷ������Ƴ��� message)
 *
 * ֻ����Ϣ��δ������ʱ�ſ��Ա�ȡ��
 *
 * \retval  AW_OK       �ɹ�
 * \retval  AW_ERROR    ʧ�ܣ�message���ڱ�����
 * \attention ���ô˺�����������������
 */
aw_local aw_inline aw_err_t awbl_i2c_msg_cancel (struct aw_i2c_message *p_msg)
{
    if ((p_msg->status == -ENOTCONN) ||
        (p_msg->status == -EISCONN)) {

        aw_list_del((struct aw_list_head *)p_msg->ctlrdata);
        return AW_OK;
    }

    return AW_ERROR;
}

/**
 * \brief �������������б��Ƿ�Ϊ��
 * \attention ���ô˺�����������������
 */
aw_local aw_inline int awbl_i2c_msg_empty (struct awbl_i2c_master *p_master)
{
    return aw_list_empty_careful(&p_master->msg_list);
}

/**
 * \brief AWBus i2c ����ģ���ʼ������
 *
 * \attention ������Ӧ���� awbus_lite_init() ֮��awbl_dev_init1() ֮ǰ����
 */
void awbl_i2cbus_init(void);

/**
 * \brief ���� AWBus I2C ����ʵ���Լ�ö�������ϵ��豸
 *
 * ���ӿ��ṩ�� AWBus I2C ���߿�����(�����豸)����ʹ��
 *
 */
aw_err_t awbl_i2cbus_create(struct awbl_i2c_master *p_master);

/**
 * \brief ������Ϣ���첽ģʽ
 *
 * ���ӿ��ṩ�� AWBus I2C ���豸����ʹ��
 *
 * ���첽�ķ�ʽ������Ϣ����Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status��
 * ��Ϣ�������(�ɹ�����ʱ�����)ʱ��������� p_msg->pfunc_complete ������
 * ���� p_msg->p_arg��
 *
 * \param[in]       p_dev   AWBus I2C ���豸ʵ��
 * \param[in,out]   p_msg   Ҫ�������Ϣ
 *
 * �����ķ���ֵ���£�
 * \retval  AW_OK       ��Ϣ�Ŷӳɹ����ȴ�����
 * \retval  -EINVAL     ��������
 *
 * �ɹ�����Ĵ��������ӳ�� p_msg->done_num
 *
 * ��Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status ��
 *
 *      \li  -ENOTCONN       ��Ϣ��δ�Ŷ�
 *      \li  -EISCONN        ��Ϣ�����ŶӴ���
 *      \li  -EINPROGRESS    ��Ϣ���ڱ�����
 * ����Ϊ��Ϣ������ϵĽ�� (��ͨ�� p_msg->done_num ��λ����Ĵ���)
 *      \li  AW_OK           ���д���ɹ�����
 *      \li  -ENOTSUP        ĳ�δ���Ŀ��Ʊ�־��֧��
 *      \li  -ETIME          ��ʱ����Ϣδ���趨��ʱ���ڴ����ڿ�������devinfo��
 *                           ���ó�ʱʱ��
 *      \li  -ENODEV         ĳ�δ����Ŀ���ַ��Ӧ��
 *      \li  -ENOENT         ĳ�δ��䷢�͵�������Ӧ��
 *      \li  -EIO            ������Ϣʱ�������ߴ��������ٲ�ʧ�ܹ���ȴ���
 *      \li  -ECANCELED      �����������������������Ϣ��ȡ�������Ժ�����
 */
aw_err_t awbl_i2c_async(struct awbl_i2c_device *p_dev,
                        struct aw_i2c_message  *p_msg);

/**
 * \brief ������Ϣ��ͬ��ģʽ
 *
 * ���ӿ��ṩ�� AWBus I2C ���豸����ʹ��
 *
 * ��ͬ���ķ�ʽ������Ϣ����Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status��
 * ���� p_msg->pfunc_complete �� p_msg->p_arg �ɿ�����ʹ�á�
 *
 * \param[in]       p_dev   AWBus I2C ���豸ʵ��
 * \param[in,out]   p_msg   Ҫ�������Ϣ
 *
 * �����ķ���ֵ���£�
 * \retval AW_OK        ��Ϣ����ɹ�
 * \retval -AW_EINVAL   ��������p_msg ��ĳЩ��Ա������Ч������
 * \retval -ENOTSUP     ��Ϣ��ĳЩ�������õ� ���Բ�֧��
 *                      (����, AW_I2C_M_IGNORE_NAK)
 * \retval -ETIME       ��ʱ����Ϣδ���趨��ʱ���ڴ����ڿ�������devinfo��
 *                      ���ó�ʱʱ��
 * \retval -ENODEV      ĳ�δ����Ŀ���ַ��Ӧ��
 * \retval -ENOENT      ĳ�δ��䷢�͵�������Ӧ��
 * \retval -EIO         ������Ϣʱ�������ߴ��������ٲ�ʧ�ܹ���ȴ���
 * \retval -ECANCELED   �����������������������Ϣ��ȡ�������Ժ�����
 *
 * �ɹ�����Ĵ��������ӳ�� p_msg->done_num
 *
 * ��Ϣ�Ĵ���״̬�ͽ����ӳ�� p_msg->status ��
 *
 *      \li  -ENOTCONN       ��Ϣ��δ�Ŷ�
 *      \li  -EISCONN        ��Ϣ�����ŶӴ���
 *      \li  -EINPROGRESS    ��Ϣ���ڱ�����
 * ����Ϊ��Ϣ������ϵĽ�� (��ͨ�� p_msg->done_num ��λ����Ĵ���)
 *      \li  AW_OK           ���д���ɹ�����
 *      \li  -ENOTSUP        ĳ�δ���Ŀ��Ʊ�־��֧��
 *      \li  -ETIME          ��ʱ����Ϣδ���趨��ʱ���ڴ���
 *      \li  -ENODEV         ĳ�δ����Ŀ���ַ��Ӧ��
 *      \li  -ENOENT         ĳ�δ��䷢�͵�������Ӧ��
 *      \li  -EIO            ������Ϣʱ�������ߴ��������ٲ�ʧ�ܹ���ȴ���
 *      \li  -ECANCELED      �����������������������Ϣ��ȡ�������Ժ�����
 */
aw_err_t awbl_i2c_sync(struct awbl_i2c_device *p_dev,
                       struct aw_i2c_message  *p_msg);

/**
 * \brief ��I2C�ӻ�����
 *
 * ���ӿ��ṩ�� AWBus I2C ���豸����ʹ��
 *
 * \param[in]  p_dev    AWBus I2C�ӻ��豸ʵ���� �� \ref struct awbl_i2c_device
 * \param[in]  flags    �ӻ��豸���ԣ�����I2C���豸���Ա�־ (aw_i2c.h)��
 * \param[in]  addr     �ӻ��豸��ַ��7λ��10λ
 * \param[in]  subaddr  �������ӵ�ַ���Ӵ˵�ַ��ʼ��ȡ���ݣ��� flags �����ӵ�ַ
 *                      ���Ϊ0 (AW_I2C_SUBADDR_NONE), ��˲�����������
 * \param[out] p_buf    ���ݻ���������ȡ�����ݴ���ڴ�
 * \param[in]  nbytes   Ҫд������ݸ���
 *
 * \retval AW_OK        ��ȡ�ɹ�
 * \retval -ENXIO       δ�ҵ����豸��������
 * \retval -EFAULT      p_buf Ϊ NULL
 * \retval -AW_EINVAL   ��������nbytes Ϊ 0
 * \retval -ENOTSUP     flags ��ĳЩ���Բ�֧�� (����, AW_I2C_IGNORE_NAK)
 * \retval -ETIME       ��ʱ����Ϣδ���趨��ʱ���ڴ����ڿ�������devinfo��
 *                      ���ó�ʱʱ��
 * \retval -ENODEV      �ӻ���ַ��Ӧ��(�� flags ������ AW_I2C_IGNORE_NAK,
 *                      �򲻻�����˴���)
 * \retval -ENOENT      ������Ӧ��(�� flags ������ AW_I2C_IGNORE_NAK,
 *                      �򲻻�����˴���)
 * \retval -EIO         ��д����ʱ�������ߴ��������ٲ�ʧ�ܹ���ȴ���
 * \retval -ECANCELED   �������������д������ȡ�������Ժ�����
 *
 * \par ����
 * \code
 *  uint8_t read_buf[16];
 *
 *  awbl_i2c_read((struct awbl_i2c_device *)p_dev,  // AWBus ���豸ʵ��
 *                 AW_I2C_ADDR_7BIT |
 *                 AW_I2C_SUBADDR_1BYTE,  // 7-bit ������ַ 1-byte �������ӵ�ַ
 *                 0x50,                 // ������ַ��0x50
 *                 0,                    // �������ӵ�ַ��0x00
 *                 p_buf,                // ��������
 *                 16);                  // ��ȡ���ݳ��ȣ�16�ֽ�
 * \endcode
 */
aw_err_t awbl_i2c_read(struct awbl_i2c_device *p_dev,
                       uint16_t                flags,
                       uint16_t                addr,
                       uint32_t                subaddr,
                       void                   *p_buf,
                       size_t                  nbytes);

/**
 * \brief д���ݵ�I2C�ӻ�
 *
 * ���ӿ��ṩ�� AWBus I2C ���豸����ʹ��
 *
 * \param[in]  p_dev    AWBus I2C�ӻ��豸ʵ���� �� \ref struct awbl_i2c_device
 * \param[in]  flags    �ӻ��豸���ԣ�����I2C���豸���Ա�־ (aw_i2c.h)��
 * \param[in]  addr     �ӻ��豸��ַ��7λ��10λ
 * \param[in]  subaddr  �������ӵ�ַ���Ӵ˵�ַ��ʼ��ȡ���ݣ��� flags �����ӵ�ַ
 *                      ���Ϊ0 (AW_I2C_SUBADDR_NONE), ��˲�����������
 * \param[out] p_buf    ���ݻ�������Ҫд������ݴ���ڴ�
 * \param[in]  nbytes   Ҫд������ݸ���
 *
 * \retval AW_OK        ��ȡ�ɹ�
 * \retval -ENXIO       δ�ҵ����豸��������
 * \retval -EFAULT      p_buf Ϊ NULL
 * \retval -AW_EINVAL   ��������nbytes Ϊ 0
 * \retval -ENOTSUP     flags ��ĳЩ���Բ�֧�� (����, AW_I2C_IGNORE_NAK)
 * \retval -ETIME       ��ʱ����Ϣδ���趨��ʱ���ڴ����ڿ�������devinfo��
 *                      ���ó�ʱʱ��
 * \retval -ENODEV      �ӻ���ַ��Ӧ��(�� flags ������ AW_I2C_IGNORE_NAK,
 *                      �򲻻�����˴���)
 * \retval -ENOENT      ������Ӧ��(�� flags ������ AW_I2C_IGNORE_NAK,
 *                      �򲻻�����˴���)
 * \retval -EIO         ��д����ʱ�������ߴ��������ٲ�ʧ�ܹ���ȴ���
 * \retval -ECANCELED   �������������д������ȡ�������Ժ�����
 *
 * \par ����
 * \code
 *  uint8_t write_buf[16];
 *
 *  awbl_i2c_write((struct awbl_i2c_device *)p_dev,  // AWBus ���豸ʵ��
 *                  AW_I2C_ADDR_7BIT |
 *                  AW_I2C_SUBADDR_1BYTE,  // 7-bit ������ַ 1-byte �������ӵ�ַ
 *                  0x50,                 // ������ַ��0x50
 *                  0,                    // �������ӵ�ַ��0x00
 *                  p_buf,                // ��������
 *                  16);                  // ��ȡ���ݳ��ȣ�16�ֽ�
 * \endcode
 */
aw_err_t awbl_i2c_write(struct awbl_i2c_device *p_dev,
                        uint16_t                flags,
                        uint16_t                addr,
                        uint32_t                subaddr,
                        const void             *p_buf,
                        size_t                  nbytes);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_I2CBUS_H */

/* end of file */
