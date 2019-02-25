/*******************************************************************************
*                                 AnyWhere
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Ti EDMA3 ��׼�ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_ti_edma3.h"
 * \endcode
 *
 * \par ��ʾ��
 * \code
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 13-12-02  yangtao, first implementation
 * \endinternal
 */

#ifndef __AW_TI_EDMA3_H
#define __AW_TI_EDMA3_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_ti_edma3
 * \copydetails aw_ti_edma3.h
 * @{
 */

#include "driver/dma/awbl_ti_edma3_private.h"

/** \brief ���� DMA ��������Ԫ�� */
#define AW_TI_EDMA3_UNIT_ANY            (-1)

/** \brief ���� DMA ͨ�� */
#define AW_TI_EDMA3_DMA_CHAN_ANY        EDMA3_DRV_DMA_CHANNEL_ANY

/** \brief ���� QDMA ͨ�� */
#define AW_TI_EDMA3_QDMA_CHAN_ANY       EDMA3_DRV_QDMA_CHANNEL_ANY

/** \brief ���� TCC */
#define AW_TI_EDMA3_TCC_ANY             EDMA3_DRV_TCC_ANY

/** \brief ������õ� PaRAM Set */
#define AW_TI_EDMA3_LINK_CHAN           EDMA3_DRV_LINK_CHANNEL

/** \brief ������õ� PaRAM Set ��ָ�� TCC */
#define AW_TI_EDMA3_LINK_CHAN_WITH_TCC  EDMA3_DRV_LINK_CHANNEL_WITH_TCC


/**
 * \name PaRAM set OPT �����
 * @{
 */

/* Դ��ַģʽ */
#define EDMA3_OPT_SAM_INCR          AW_SBF(0, 0)
#define EDMA3_OPT_SAM_CONST         AW_SBF(1, 0)

/* Ŀ���ַģʽ */
#define EDMA3_OPT_DAM_INCR          AW_SBF(0, 1)
#define EDMA3_OPT_DAM_CONST         AW_SBF(1, 1)

/* ����ͬ��ģʽ */
#define EDMA3_OPT_SYNCDIM_A         AW_SBF(0, 2)
#define EDMA3_OPT_SYNCDIM_AB        AW_SBF(1, 2)

/* ��̬ PaRAM Set */
#define EDMA3_OPT_STATIC_NOT        AW_SBF(0, 3)
#define EDMA3_OPT_STATIC            AW_SBF(1, 3)

/* FIFO ��� (EDMA3_OPT_SAM_CONST �� EDMA3_OPT_DAM_CONST ʱ��Ч) */
#define EDMA3_OPT_FWID_8_BIT        AW_SBF(0, 8)
#define EDMA3_OPT_FWID_16_BIT       AW_SBF(1, 8)
#define EDMA3_OPT_FWID_32_BIT       AW_SBF(2, 8)
#define EDMA3_OPT_FWID_64_BIT       AW_SBF(3, 8)
#define EDMA3_OPT_FWID_128_BIT      AW_SBF(4, 8)
#define EDMA3_OPT_FWID_256_BIT      AW_SBF(5, 8)

/* ���������ģʽ */
#define EDMA3_OPT_TCCMODE_NORMAL    AW_SBF(0, 11)
#define EDMA3_OPT_TCCMODE_EARLY     AW_SBF(1, 11)

/* TCC (���������) */
#define EDMA3_OPT_TCC(tcc)          AW_SBF(tcc, 12)

/* ��������ж�ʹ�� */
#define EDMA3_OPT_TCINTEN_OFF       AW_SBF(0, 20)
#define EDMA3_OPT_TCINTEN_ON        AW_SBF(1, 20)

/* �м䴫������ж�ʹ�� */
#define EDMA3_OPT_ITCINTEN_OFF      AW_SBF(0, 21)
#define EDMA3_OPT_ITCINTEN_ON       AW_SBF(1, 21)

/* �����������ʹ�� */
#define EDMA3_OPT_TCCHEN_OFF        AW_SBF(0, 22)
#define EDMA3_OPT_TCCHEN_ON         AW_SBF(1, 22)

/* �м䴫���������ʹ�� */
#define EDMA3_OPT_ITCCHEN_OFF       AW_SBF(0, 23)
#define EDMA3_OPT_ITCCHEN_ON        AW_SBF(1, 23)

/** @} */


/**
 * \enum    aw_ti_edma3_tcc_status
 * \brief   ������ EDMA3 �����״̬���͡�������ͨ���Ļص�����ʱ���ڸ�֪״̬��
 */
typedef enum aw_ti_edma3_tcc_status {

    /**
     * \brief DMA ����ɹ����[�����(true completion)ģʽ]�����ύ��TC
     * [�����(early completion)ģʽ]
     */
    EDMA3_XFER_COMPLETE = 1,

    /** \brief DMA �¼���ʧ */
    EDMA3_E_CC_DMA_EVT_MISS = 2,

    /** \brief QDMA �¼���ʧ*/
    EDMA3_E_CC_QDMA_EVT_MISS = 3

} aw_ti_edma3_tcc_status_t;

/**
 * \brief EDMA������ʽ
 *
 * ʹ������Ķ�����ѡ��EDMA����ģʽ
 */
typedef enum  aw_ti_edma3_trigger_mode {

    /**
     * \brief �ֶ�����ģʽ
     *
     * ͨ�����¼����Ĵ��� (ESR/ESRH) ��Ӧ��λд��1���ֶ�����һ�δ���
     */
    EDMA3_TRIG_MODE_MANUAL = 0,

    /**
     * \brief QDMA ��ʼ��ģʽ
     *
     * ��CPU (������EDMA3����) д QDMA ͨ���������Ĵ�����(�Զ�����) ���� EDMA3CC
     * ִ���Ѿ���ӳ�䵽QDMAͨ���Ĳ������ϵ����Ӹ���(���Ӵ���)ʱ��һ��QDMA���䱻
     * ������
     */
    EDMA3_TRIG_MODE_QDMA = 1,

    /**
     * \brief �¼�����ģʽ
     *
     * �������衢ϵͳ�������ⲿ�¼�������һ�δ�������
     */
    EDMA3_TRIG_MODE_EVENT = 2,

    /**
     * \brief ����ָ���޴���ģʽ
     */
    EDMA3_TRIG_MODE_NONE = 3

} aw_ti_edma3_trigger_mode_t;

typedef struct aw_ti_edma3_chan_res *aw_ti_edma3_chan_id_t;

/**
 * \brief  Channel �ص�����
 *
 * \param chan_id   ͨ����
 * \param status    ����״̬
 * \param cb_data   ���ݸ��ص������Ĳ���(ע��ص�����ʱ����)
 */
typedef void (* aw_ti_edma3_chan_callback_t)(aw_ti_edma3_chan_id_t    chan_id,
                                             aw_ti_edma3_tcc_status_t status,
                                             void *cb_data);

/**
 * \brief DMA  Channel ��Դ������ DMA��QDMA��Link ͨ��
 */
typedef struct aw_ti_edma3_chan_res {
    uint32_t                    unit;           /* EDMA3��������Ԫ�� */
    uint32_t                    chan_id;        /* ͨ��ID */
    uint32_t                    tcc;            /* ͨ����Ӧ�� TCC �� */
    uint32_t                    evt_queue;      /* ͨ��ʹ�õĶ��к� */
    aw_ti_edma3_chan_callback_t chan_cb;        /* �ص�����  */
    void                       *cb_data;        /* �ص��������� */
    aw_ti_edma3_trigger_mode_t  trigger_mode;   /* ����ģʽ */
    int                         region_id;      /* ͨ��������ID */
    void                       *p_cookie;       /* �ڲ�ʹ�� */
} aw_ti_edma3_chan_res_t;

/**
 * \brief EDMA3 Parameter RAM Set in User Configurable format
 *
 * This is a mapping of the EDMA3 PaRAM set provided to the user
 * for ease of modification of the individual fields
 */
typedef struct  {
        /** OPT field of PaRAM Set */
        volatile uint32_t opt;

        /**
         * \brief Starting byte address of Source
         * For FIFO mode, srcAddr must be a 256-bit aligned address.
         */
        volatile uint32_t src_addr;

        /**
         * \brief Number of bytes in each Array (ACNT)
         */
        volatile uint16_t a_cnt;

        /**
         * \brief Number of Arrays in each Frame (BCNT)
         */
        volatile uint16_t b_cnt;

        /**
         * \brief Starting byte address of destination
         * For FIFO mode, destAddr must be a 256-bit aligned address.
         * i.e. 5 LSBs should be 0.
         */
        volatile uint32_t dst_addr;

        /**
         * \brief Index between consec. arrays of a Source Frame (SRCBIDX)
         * If SAM is set to 1 (via channelOptions) then srcInterArrIndex should
         * be an even multiple of 32 bytes.
         */
        volatile int16_t  src_b_idx;

        /**
         * \brief Index between consec. arrays of a Destination Frame (DSTBIDX)
         * If DAM is set to 1 (via channelOptions) then destInterArrIndex should
         * be an even multiple of 32 bytes
         */
        volatile int16_t  dst_b_idx;

        /**
         * \brief Address for linking (AutoReloading of a PaRAM Set)
         * This must point to a valid aligned 32-byte PaRAM set
         * A value of 0xFFFF means no linking
         * Linking is especially useful for use with ping-pong buffers and
         * circular buffers
         */
        volatile uint16_t link_addr;

        /**
         * \brief Reload value of the numArrInFrame (BCNT)
         * Relevant only for A-sync transfers
         */
        volatile uint16_t b_cnt_reload;

        /**
         * \brief Index between consecutive frames of a Source Block (SRCCIDX)
         */
        volatile int16_t  src_c_idx;

        /**
         * \brief Index between consecutive frames of a Dest Block (DSTCIDX)
         */
        volatile int16_t  dst_c_idx;

        /**
         * \brief Number of Frames in a block (CCNT)
         */
        volatile uint16_t c_cnt;

        /**
         * \brief Reserved
         */
        volatile int16_t  reserved;
} aw_ti_edma3_param_regs_t;

/**
 * \brief   QDMA ������
 */
typedef enum
{
        /**
         * Set the OPT field (Offset Address 0h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_OPT                  = 0,
        /**
         * Set the SRC field (Offset Address 4h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_SRC                  = 1,
        /**
         * Set the (ACNT + BCNT) field (Offset Address 8h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_ACNT_BCNT            = 2,
        /**
         * Set the DST field (Offset Address Ch Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_DST                  = 3,
        /**
         * Set the (SRCBIDX + DSTBIDX) field (Offset Address 10h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_SRC_DST_BIDX         = 4,
        /**
         * Set the (LINK + BCNTRLD) field (Offset Address 14h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_LINK_BCNTRLD         = 5,
        /**
         * Set the (SRCCIDX + DSTCIDX) field (Offset Address 18h Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_SRC_DST_CIDX         = 6,
        /**
         * Set the (CCNT + RSVD) field (Offset Address 1Ch Bytes)
         * as the QDMA trigger word
         */
        EDMA3_QDMA_TRIG_CCNT                 = 7,

        /** Default Trigger Word */
        EDMA3_QDMA_TRIG_DEFAULT              = 7
} aw_ti_edma3_qdma_trig_word_t;

typedef enum
{
    /**
     * A-synchronized.
     * Each event triggers the transfer of a single array of ACNT bytes
     */
    EDMA3_SYNC_A = 0 ,

    /**
     * AB-synchronized.
     * Each event triggers the transfer of BCNT arrays of ACNT bytes
     */
    EDMA3_SYNC_AB = 1

} aw_ti_edma3_sync_type_t;

typedef enum
{
        /**
         * Source addressing mode (INCR / FIFO)
         * (Bit 0)
         */
        EDMA3_OPT_FIELD_SAM = 0,

        /**
         * Destination addressing mode (INCR / FIFO)
         * (Bit 1)
         */
        EDMA3_OPT_FIELD_DAM = 1,

        /**
         * Transfer synchronization dimension (A-synchronized / AB-synchronized)
         * (Bit 2)
         */
        EDMA3_OPT_FIELD_SYNCDIM = 2,

        /**
         * The STATIC field
         * PaRAM set is static/non-static?
         * (Bit 3)
         */
        EDMA3_OPT_FIELD_STATIC  = 3,

        /**
         * FIFO Width. Applies if either SAM or DAM is set to FIFO mode.
         * (Bitfield 8-10)
         */
        EDMA3_OPT_FIELD_FWID = 4,

        /**
         * Transfer complete code mode. Indicates the point at which a
         * transfer is considered completed for chaining and interrupt
         * generation.
         * (Bit 11)
         */
        EDMA3_OPT_FIELD_TCCMODE = 5,

        /**
         * Transfer Complete Code (TCC).
         * This 6-bit code is used to set the relevant bit in chaining enable
         * register (CER[TCC]/CERH[TCC]) for chaining or in interrupt pending
         * register (IPR[TCC]/IPRH[TCC]) for interrupts.
         * (Bitfield 12-17)
         */
        EDMA3_OPT_FIELD_TCC = 6,

        /**
         * Transfer complete interrupt enable/disable.
         * (Bit 20)
         */
        EDMA3_OPT_FIELD_TCINTEN = 7,

        /**
         * Intermediate transfer complete interrupt enable/disable.
         * (Bit 21)
         */
        EDMA3_OPT_FIELD_ITCINTEN = 8,

        /**
         * Transfer complete chaining enable/disable
         * (Bit 22)
         */
        EDMA3_OPT_FIELD_TCCHEN = 9,

        /**
         * Intermediate transfer completion chaining enable/disable
         * (Bit 23)
         */
        EDMA3_OPT_FIELD_ITCCHEN = 10

} aw_ti_edma3_opt_field_t ;

typedef enum
{
        /**
         * Increment (INCR) mode. Source addressing within an array increments.
         * Source is not a FIFO.
         */
        EDMA3_ADDR_MODE_INCR            = 0,

        /**
         * FIFO mode. Source addressing within an array wraps around upon
         * reaching FIFO width.
         */
        EDMA3_ADDR_MODE_FIFO            = 1

} aw_ti_edma3_addr_mode_t;

typedef enum
{
        /** FIFO width is 8-bit. */
        EDMA3_W8BIT = 0,

        /** FIFO width is 16-bit. */
        EDMA3_W16BIT = 1,

        /** FIFO width is 32-bit. */
        EDMA3_W32BIT = 2,

        /** FIFO width is 64-bit. */
        EDMA3_W64BIT = 3,

        /** FIFO width is 128-bit. */
        EDMA3_W128BIT = 4,

        /** FIFO width is 256-bit. */
        EDMA3_W256BIT = 5

} aw_ti_edma3_fifo_width_t;

typedef enum
{
    /**
     * The OPT field (Offset Address 0x0 Bytes)
     */
    EDMA3_PARAM_ENTRY_OPT                       = 0,

    /**
     * The SRC field (Offset Address 0x4 Bytes)
     */
    EDMA3_PARAM_ENTRY_SRC                       = 1,

    /**
     * The (ACNT+BCNT) field (Offset Address 0x8 Bytes)
     */
    EDMA3_PARAM_ENTRY_ACNT_BCNT                 = 2,

    /**
     * The DST field (Offset Address 0xC Bytes)
     */
    EDMA3_PARAM_ENTRY_DST                       = 3,

    /**
     * The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)
     */
    EDMA3_PARAM_ENTRY_SRC_DST_BIDX              = 4,

    /**
     * The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)
     */
    EDMA3_PARAM_ENTRY_LINK_BCNTRLD              = 5,

    /**
     * The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)
     */
    EDMA3_PARAM_ENTRY_SRC_DST_CIDX              = 6,

    /**
     * The (CCNT+RSVD) field (Offset Address 0x1C Bytes)
     */
    EDMA3_PARAM_ENTRY_CCNT                      = 7

} aw_ti_edma3_param_entry_t;


/**
 * \brief ����DMAͨ��
 *
 * TODO
 * \return              DMA ͨ��ID, NULL��ʾ����ʧ��
 */
aw_err_t aw_ti_edma3_chan_alloc(aw_ti_edma3_chan_res_t *p_chan_res,
                                int    unit,
                                int    chan_id,
                                int    tcc,
                                int    evt_queue,
                                aw_ti_edma3_chan_callback_t  tcc_cb,
                                void  *cb_data);

/**
 * TODO
 */

aw_err_t aw_ti_edma3_chan_free(aw_ti_edma3_chan_res_t *p_chan_res);

aw_err_t aw_ti_edma3_set_param(aw_ti_edma3_chan_res_t *p_chan_res,
                               aw_ti_edma3_param_regs_t *p_param);

aw_err_t aw_ti_edma3_enable_transfer(aw_ti_edma3_chan_res_t *p_chan_res,
                                    aw_ti_edma3_trigger_mode_t trigger_mode);

aw_err_t aw_ti_edma3_disable_transfer(aw_ti_edma3_chan_res_t *p_chan_res);

aw_err_t aw_ti_edma3_clear_error_bits(aw_ti_edma3_chan_res_t *p_chan_res);

aw_err_t aw_ti_edma3_link_chan (aw_ti_edma3_chan_res_t *p_chan_res1,
                                aw_ti_edma3_chan_res_t *p_chan_res2);

aw_err_t aw_ti_edma3_set_qdma_trig_word (aw_ti_edma3_chan_res_t      *p_chan_res,
                                         aw_ti_edma3_qdma_trig_word_t trig_word);

aw_err_t aw_ti_edma3_set_qdma_trig_word (aw_ti_edma3_chan_res_t      *p_chan_res,
                                         aw_ti_edma3_qdma_trig_word_t trig_word);

aw_err_t aw_ti_edma3_set_src_index (aw_ti_edma3_chan_res_t  *p_chan_res,
                                    int16_t                  src_b_idx,
                                    int16_t                  src_c_idx);

aw_err_t aw_ti_edma3_set_dst_index (aw_ti_edma3_chan_res_t  *p_chan_res,
                                    int16_t                  dst_b_idx,
                                    int16_t                  dst_c_idx);

aw_err_t aw_ti_edma3_set_trans_params (aw_ti_edma3_chan_res_t  *p_chan_res,
                                       uint16_t                 a_cnt,
                                       uint16_t                 b_cnt,
                                       uint16_t                 c_cnt,
                                       uint16_t                 b_cnt_reload,
                                       aw_ti_edma3_sync_type_t  sync_type);

aw_err_t aw_ti_edma3_set_opt_field (aw_ti_edma3_chan_res_t  *p_chan_res,
                                    aw_ti_edma3_opt_field_t  opt_field,
                                    uint32_t                 value);

aw_err_t aw_ti_edma3_get_opt_field (aw_ti_edma3_chan_res_t  *p_chan_res,
                                    aw_ti_edma3_opt_field_t  opt_field,
                                    uint32_t                *p_value);

aw_err_t aw_ti_edma3_set_src_params (aw_ti_edma3_chan_res_t  *p_chan_res,
                                     uint32_t                 src_addr,
                                     aw_ti_edma3_addr_mode_t  addr_mode,
                                     aw_ti_edma3_fifo_width_t fifo_width);

aw_err_t aw_ti_edma3_set_param_entry (aw_ti_edma3_chan_res_t   *p_chan_res,
                                      aw_ti_edma3_param_entry_t param_entry,
                                      uint32_t                  value);

aw_err_t aw_ti_edma3_get_param_entry (aw_ti_edma3_chan_res_t    *p_chan_res,
                                      aw_ti_edma3_param_entry_t  param_entry,
                                      uint32_t                  *p_value);

aw_ti_edma3_param_regs_t *
    aw_ti_edma3_get_param_regs_addr (aw_ti_edma3_chan_res_t   *p_chan_res);

/** @}  grp_aw_if_ti_edma3 */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_TI_EDMA3_H */

/* end of file */

