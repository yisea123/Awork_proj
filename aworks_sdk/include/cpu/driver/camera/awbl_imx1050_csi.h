/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_IMX1050_CSI_H
#define __AWBL_IMX1050_CSI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_list.h"
#include "aw_sem.h"
#include "aw_task.h"
#include "driver/camera/awbl_camera.h"


#define AWBL_IMX1050_CSI_NAME   "imx1050_csi"

/** \brief csi 任务的栈  */
#define __IMX1050_CSI_TASK_STACK_SIZE   (1024)

/** \brief 通过分辨率提取宽和高  */
#define VIDEO_EXTRACT_WIDTH(resolution) ((uint16_t)((resolution)&0xFFFFU))
#define VIDEO_EXTRACT_HEIGHT(resolution) ((uint16_t)((resolution) >> 16U))


/** \brief CSICR1 - CSI Control Register 1 */
#define CSI_CSICR1_PIXEL_BIT_MASK                (0x1U)
#define CSI_CSICR1_PIXEL_BIT_SHIFT               (0U)
#define CSI_CSICR1_PIXEL_BIT(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_PIXEL_BIT_SHIFT)) & CSI_CSICR1_PIXEL_BIT_MASK)
#define CSI_CSICR1_REDGE_MASK                    (0x2U)
#define CSI_CSICR1_REDGE_SHIFT                   (1U)
#define CSI_CSICR1_REDGE(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_REDGE_SHIFT)) & CSI_CSICR1_REDGE_MASK)
#define CSI_CSICR1_INV_PCLK_MASK                 (0x4U)
#define CSI_CSICR1_INV_PCLK_SHIFT                (2U)
#define CSI_CSICR1_INV_PCLK(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_INV_PCLK_SHIFT)) & CSI_CSICR1_INV_PCLK_MASK)
#define CSI_CSICR1_INV_DATA_MASK                 (0x8U)
#define CSI_CSICR1_INV_DATA_SHIFT                (3U)
#define CSI_CSICR1_INV_DATA(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_INV_DATA_SHIFT)) & CSI_CSICR1_INV_DATA_MASK)
#define CSI_CSICR1_GCLK_MODE_MASK                (0x10U)
#define CSI_CSICR1_GCLK_MODE_SHIFT               (4U)
#define CSI_CSICR1_GCLK_MODE(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_GCLK_MODE_SHIFT)) & CSI_CSICR1_GCLK_MODE_MASK)
#define CSI_CSICR1_CLR_RXFIFO_MASK               (0x20U)
#define CSI_CSICR1_CLR_RXFIFO_SHIFT              (5U)
#define CSI_CSICR1_CLR_RXFIFO(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_CLR_RXFIFO_SHIFT)) & CSI_CSICR1_CLR_RXFIFO_MASK)
#define CSI_CSICR1_CLR_STATFIFO_MASK             (0x40U)
#define CSI_CSICR1_CLR_STATFIFO_SHIFT            (6U)
#define CSI_CSICR1_CLR_STATFIFO(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_CLR_STATFIFO_SHIFT)) & CSI_CSICR1_CLR_STATFIFO_MASK)
#define CSI_CSICR1_PACK_DIR_MASK                 (0x80U)
#define CSI_CSICR1_PACK_DIR_SHIFT                (7U)
#define CSI_CSICR1_PACK_DIR(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_PACK_DIR_SHIFT)) & CSI_CSICR1_PACK_DIR_MASK)
#define CSI_CSICR1_FCC_MASK                      (0x100U)
#define CSI_CSICR1_FCC_SHIFT                     (8U)
#define CSI_CSICR1_FCC(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_FCC_SHIFT)) & CSI_CSICR1_FCC_MASK)
#define CSI_CSICR1_CCIR_EN_MASK                  (0x400U)
#define CSI_CSICR1_CCIR_EN_SHIFT                 (10U)
#define CSI_CSICR1_CCIR_EN(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_CCIR_EN_SHIFT)) & CSI_CSICR1_CCIR_EN_MASK)
#define CSI_CSICR1_HSYNC_POL_MASK                (0x800U)
#define CSI_CSICR1_HSYNC_POL_SHIFT               (11U)
#define CSI_CSICR1_HSYNC_POL(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_HSYNC_POL_SHIFT)) & CSI_CSICR1_HSYNC_POL_MASK)
#define CSI_CSICR1_SOF_INTEN_MASK                (0x10000U)
#define CSI_CSICR1_SOF_INTEN_SHIFT               (16U)
#define CSI_CSICR1_SOF_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_SOF_INTEN_SHIFT)) & CSI_CSICR1_SOF_INTEN_MASK)
#define CSI_CSICR1_SOF_POL_MASK                  (0x20000U)
#define CSI_CSICR1_SOF_POL_SHIFT                 (17U)
#define CSI_CSICR1_SOF_POL(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_SOF_POL_SHIFT)) & CSI_CSICR1_SOF_POL_MASK)
#define CSI_CSICR1_RXFF_INTEN_MASK               (0x40000U)
#define CSI_CSICR1_RXFF_INTEN_SHIFT              (18U)
#define CSI_CSICR1_RXFF_INTEN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_RXFF_INTEN_SHIFT)) & CSI_CSICR1_RXFF_INTEN_MASK)
#define CSI_CSICR1_FB1_DMA_DONE_INTEN_MASK       (0x80000U)
#define CSI_CSICR1_FB1_DMA_DONE_INTEN_SHIFT      (19U)
#define CSI_CSICR1_FB1_DMA_DONE_INTEN(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_FB1_DMA_DONE_INTEN_SHIFT)) & CSI_CSICR1_FB1_DMA_DONE_INTEN_MASK)
#define CSI_CSICR1_FB2_DMA_DONE_INTEN_MASK       (0x100000U)
#define CSI_CSICR1_FB2_DMA_DONE_INTEN_SHIFT      (20U)
#define CSI_CSICR1_FB2_DMA_DONE_INTEN(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_FB2_DMA_DONE_INTEN_SHIFT)) & CSI_CSICR1_FB2_DMA_DONE_INTEN_MASK)
#define CSI_CSICR1_STATFF_INTEN_MASK             (0x200000U)
#define CSI_CSICR1_STATFF_INTEN_SHIFT            (21U)
#define CSI_CSICR1_STATFF_INTEN(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_STATFF_INTEN_SHIFT)) & CSI_CSICR1_STATFF_INTEN_MASK)
#define CSI_CSICR1_SFF_DMA_DONE_INTEN_MASK       (0x400000U)
#define CSI_CSICR1_SFF_DMA_DONE_INTEN_SHIFT      (22U)
#define CSI_CSICR1_SFF_DMA_DONE_INTEN(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_SFF_DMA_DONE_INTEN_SHIFT)) & CSI_CSICR1_SFF_DMA_DONE_INTEN_MASK)
#define CSI_CSICR1_RF_OR_INTEN_MASK              (0x1000000U)
#define CSI_CSICR1_RF_OR_INTEN_SHIFT             (24U)
#define CSI_CSICR1_RF_OR_INTEN(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_RF_OR_INTEN_SHIFT)) & CSI_CSICR1_RF_OR_INTEN_MASK)
#define CSI_CSICR1_SF_OR_INTEN_MASK              (0x2000000U)
#define CSI_CSICR1_SF_OR_INTEN_SHIFT             (25U)
#define CSI_CSICR1_SF_OR_INTEN(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_SF_OR_INTEN_SHIFT)) & CSI_CSICR1_SF_OR_INTEN_MASK)
#define CSI_CSICR1_COF_INT_EN_MASK               (0x4000000U)
#define CSI_CSICR1_COF_INT_EN_SHIFT              (26U)
#define CSI_CSICR1_COF_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_COF_INT_EN_SHIFT)) & CSI_CSICR1_COF_INT_EN_MASK)
#define CSI_CSICR1_CCIR_MODE_MASK                (0x8000000U)
#define CSI_CSICR1_CCIR_MODE_SHIFT               (27U)
#define CSI_CSICR1_CCIR_MODE(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_CCIR_MODE_SHIFT)) & CSI_CSICR1_CCIR_MODE_MASK)
#define CSI_CSICR1_PrP_IF_EN_MASK                (0x10000000U)
#define CSI_CSICR1_PrP_IF_EN_SHIFT               (28U)
#define CSI_CSICR1_PrP_IF_EN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_PrP_IF_EN_SHIFT)) & CSI_CSICR1_PrP_IF_EN_MASK)
#define CSI_CSICR1_EOF_INT_EN_MASK               (0x20000000U)
#define CSI_CSICR1_EOF_INT_EN_SHIFT              (29U)
#define CSI_CSICR1_EOF_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_EOF_INT_EN_SHIFT)) & CSI_CSICR1_EOF_INT_EN_MASK)
#define CSI_CSICR1_EXT_VSYNC_MASK                (0x40000000U)
#define CSI_CSICR1_EXT_VSYNC_SHIFT               (30U)
#define CSI_CSICR1_EXT_VSYNC(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_EXT_VSYNC_SHIFT)) & CSI_CSICR1_EXT_VSYNC_MASK)
#define CSI_CSICR1_SWAP16_EN_MASK                (0x80000000U)
#define CSI_CSICR1_SWAP16_EN_SHIFT               (31U)
#define CSI_CSICR1_SWAP16_EN(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR1_SWAP16_EN_SHIFT)) & CSI_CSICR1_SWAP16_EN_MASK)

/** \brief CSICR2 - CSI Control Register 2 */
#define CSI_CSICR2_HSC_MASK                      (0xFFU)
#define CSI_CSICR2_HSC_SHIFT                     (0U)
#define CSI_CSICR2_HSC(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_HSC_SHIFT)) & CSI_CSICR2_HSC_MASK)
#define CSI_CSICR2_VSC_MASK                      (0xFF00U)
#define CSI_CSICR2_VSC_SHIFT                     (8U)
#define CSI_CSICR2_VSC(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_VSC_SHIFT)) & CSI_CSICR2_VSC_MASK)
#define CSI_CSICR2_LVRM_MASK                     (0x70000U)
#define CSI_CSICR2_LVRM_SHIFT                    (16U)
#define CSI_CSICR2_LVRM(x)                       (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_LVRM_SHIFT)) & CSI_CSICR2_LVRM_MASK)
#define CSI_CSICR2_BTS_MASK                      (0x180000U)
#define CSI_CSICR2_BTS_SHIFT                     (19U)
#define CSI_CSICR2_BTS(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_BTS_SHIFT)) & CSI_CSICR2_BTS_MASK)
#define CSI_CSICR2_SCE_MASK                      (0x800000U)
#define CSI_CSICR2_SCE_SHIFT                     (23U)
#define CSI_CSICR2_SCE(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_SCE_SHIFT)) & CSI_CSICR2_SCE_MASK)
#define CSI_CSICR2_AFS_MASK                      (0x3000000U)
#define CSI_CSICR2_AFS_SHIFT                     (24U)
#define CSI_CSICR2_AFS(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_AFS_SHIFT)) & CSI_CSICR2_AFS_MASK)
#define CSI_CSICR2_DRM_MASK                      (0x4000000U)
#define CSI_CSICR2_DRM_SHIFT                     (26U)
#define CSI_CSICR2_DRM(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_DRM_SHIFT)) & CSI_CSICR2_DRM_MASK)
#define CSI_CSICR2_DMA_BURST_TYPE_SFF_MASK       (0x30000000U)
#define CSI_CSICR2_DMA_BURST_TYPE_SFF_SHIFT      (28U)
#define CSI_CSICR2_DMA_BURST_TYPE_SFF(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_DMA_BURST_TYPE_SFF_SHIFT)) & CSI_CSICR2_DMA_BURST_TYPE_SFF_MASK)
#define CSI_CSICR2_DMA_BURST_TYPE_RFF_MASK       (0xC0000000U)
#define CSI_CSICR2_DMA_BURST_TYPE_RFF_SHIFT      (30U)
#define CSI_CSICR2_DMA_BURST_TYPE_RFF(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSICR2_DMA_BURST_TYPE_RFF_SHIFT)) & CSI_CSICR2_DMA_BURST_TYPE_RFF_MASK)

/** \brief CSICR3 - CSI Control Register 3 */
#define CSI_CSICR3_ECC_AUTO_EN_MASK              (0x1U)
#define CSI_CSICR3_ECC_AUTO_EN_SHIFT             (0U)
#define CSI_CSICR3_ECC_AUTO_EN(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_ECC_AUTO_EN_SHIFT)) & CSI_CSICR3_ECC_AUTO_EN_MASK)
#define CSI_CSICR3_ECC_INT_EN_MASK               (0x2U)
#define CSI_CSICR3_ECC_INT_EN_SHIFT              (1U)
#define CSI_CSICR3_ECC_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_ECC_INT_EN_SHIFT)) & CSI_CSICR3_ECC_INT_EN_MASK)
#define CSI_CSICR3_ZERO_PACK_EN_MASK             (0x4U)
#define CSI_CSICR3_ZERO_PACK_EN_SHIFT            (2U)
#define CSI_CSICR3_ZERO_PACK_EN(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_ZERO_PACK_EN_SHIFT)) & CSI_CSICR3_ZERO_PACK_EN_MASK)
#define CSI_CSICR3_TWO_8BIT_SENSOR_MASK          (0x8U)
#define CSI_CSICR3_TWO_8BIT_SENSOR_SHIFT         (3U)
#define CSI_CSICR3_TWO_8BIT_SENSOR(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_TWO_8BIT_SENSOR_SHIFT)) & CSI_CSICR3_TWO_8BIT_SENSOR_MASK)
#define CSI_CSICR3_RxFF_LEVEL_MASK               (0x70U)
#define CSI_CSICR3_RxFF_LEVEL_SHIFT              (4U)
#define CSI_CSICR3_RxFF_LEVEL(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_RxFF_LEVEL_SHIFT)) & CSI_CSICR3_RxFF_LEVEL_MASK)
#define CSI_CSICR3_HRESP_ERR_EN_MASK             (0x80U)
#define CSI_CSICR3_HRESP_ERR_EN_SHIFT            (7U)
#define CSI_CSICR3_HRESP_ERR_EN(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_HRESP_ERR_EN_SHIFT)) & CSI_CSICR3_HRESP_ERR_EN_MASK)
#define CSI_CSICR3_STATFF_LEVEL_MASK             (0x700U)
#define CSI_CSICR3_STATFF_LEVEL_SHIFT            (8U)
#define CSI_CSICR3_STATFF_LEVEL(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_STATFF_LEVEL_SHIFT)) & CSI_CSICR3_STATFF_LEVEL_MASK)
#define CSI_CSICR3_DMA_REQ_EN_SFF_MASK           (0x800U)
#define CSI_CSICR3_DMA_REQ_EN_SFF_SHIFT          (11U)
#define CSI_CSICR3_DMA_REQ_EN_SFF(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_DMA_REQ_EN_SFF_SHIFT)) & CSI_CSICR3_DMA_REQ_EN_SFF_MASK)
#define CSI_CSICR3_DMA_REQ_EN_RFF_MASK           (0x1000U)
#define CSI_CSICR3_DMA_REQ_EN_RFF_SHIFT          (12U)
#define CSI_CSICR3_DMA_REQ_EN_RFF(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_DMA_REQ_EN_RFF_SHIFT)) & CSI_CSICR3_DMA_REQ_EN_RFF_MASK)
#define CSI_CSICR3_DMA_REFLASH_SFF_MASK          (0x2000U)
#define CSI_CSICR3_DMA_REFLASH_SFF_SHIFT         (13U)
#define CSI_CSICR3_DMA_REFLASH_SFF(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_DMA_REFLASH_SFF_SHIFT)) & CSI_CSICR3_DMA_REFLASH_SFF_MASK)
#define CSI_CSICR3_DMA_REFLASH_RFF_MASK          (0x4000U)
#define CSI_CSICR3_DMA_REFLASH_RFF_SHIFT         (14U)
#define CSI_CSICR3_DMA_REFLASH_RFF(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_DMA_REFLASH_RFF_SHIFT)) & CSI_CSICR3_DMA_REFLASH_RFF_MASK)
#define CSI_CSICR3_FRMCNT_RST_MASK               (0x8000U)
#define CSI_CSICR3_FRMCNT_RST_SHIFT              (15U)
#define CSI_CSICR3_FRMCNT_RST(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_FRMCNT_RST_SHIFT)) & CSI_CSICR3_FRMCNT_RST_MASK)
#define CSI_CSICR3_FRMCNT_MASK                   (0xFFFF0000U)
#define CSI_CSICR3_FRMCNT_SHIFT                  (16U)
#define CSI_CSICR3_FRMCNT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CSICR3_FRMCNT_SHIFT)) & CSI_CSICR3_FRMCNT_MASK)

/** \brief CSISTATFIFO - CSI Statistic FIFO Register */
#define CSI_CSISTATFIFO_STAT_MASK                (0xFFFFFFFFU)
#define CSI_CSISTATFIFO_STAT_SHIFT               (0U)
#define CSI_CSISTATFIFO_STAT(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSISTATFIFO_STAT_SHIFT)) & CSI_CSISTATFIFO_STAT_MASK)

/** \brief CSIRFIFO - CSI RX FIFO Register */
#define CSI_CSIRFIFO_IMAGE_MASK                  (0xFFFFFFFFU)
#define CSI_CSIRFIFO_IMAGE_SHIFT                 (0U)
#define CSI_CSIRFIFO_IMAGE(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CSIRFIFO_IMAGE_SHIFT)) & CSI_CSIRFIFO_IMAGE_MASK)

/** \brief CSIRXCNT - CSI RX Count Register */
#define CSI_CSIRXCNT_RXCNT_MASK                  (0x3FFFFFU)
#define CSI_CSIRXCNT_RXCNT_SHIFT                 (0U)
#define CSI_CSIRXCNT_RXCNT(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CSIRXCNT_RXCNT_SHIFT)) & CSI_CSIRXCNT_RXCNT_MASK)

/** \brief CSISR - CSI Status Register */
#define CSI_CSISR_DRDY_MASK                      (0x1U)
#define CSI_CSISR_DRDY_SHIFT                     (0U)
#define CSI_CSISR_DRDY(x)                        (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DRDY_SHIFT)) & CSI_CSISR_DRDY_MASK)
#define CSI_CSISR_ECC_INT_MASK                   (0x2U)
#define CSI_CSISR_ECC_INT_SHIFT                  (1U)
#define CSI_CSISR_ECC_INT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_ECC_INT_SHIFT)) & CSI_CSISR_ECC_INT_MASK)
#define CSI_CSISR_HRESP_ERR_INT_MASK             (0x80U)
#define CSI_CSISR_HRESP_ERR_INT_SHIFT            (7U)
#define CSI_CSISR_HRESP_ERR_INT(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_HRESP_ERR_INT_SHIFT)) & CSI_CSISR_HRESP_ERR_INT_MASK)
#define CSI_CSISR_COF_INT_MASK                   (0x2000U)
#define CSI_CSISR_COF_INT_SHIFT                  (13U)
#define CSI_CSISR_COF_INT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_COF_INT_SHIFT)) & CSI_CSISR_COF_INT_MASK)
#define CSI_CSISR_F1_INT_MASK                    (0x4000U)
#define CSI_CSISR_F1_INT_SHIFT                   (14U)
#define CSI_CSISR_F1_INT(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_F1_INT_SHIFT)) & CSI_CSISR_F1_INT_MASK)
#define CSI_CSISR_F2_INT_MASK                    (0x8000U)
#define CSI_CSISR_F2_INT_SHIFT                   (15U)
#define CSI_CSISR_F2_INT(x)                      (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_F2_INT_SHIFT)) & CSI_CSISR_F2_INT_MASK)
#define CSI_CSISR_SOF_INT_MASK                   (0x10000U)
#define CSI_CSISR_SOF_INT_SHIFT                  (16U)
#define CSI_CSISR_SOF_INT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_SOF_INT_SHIFT)) & CSI_CSISR_SOF_INT_MASK)
#define CSI_CSISR_EOF_INT_MASK                   (0x20000U)
#define CSI_CSISR_EOF_INT_SHIFT                  (17U)
#define CSI_CSISR_EOF_INT(x)                     (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_EOF_INT_SHIFT)) & CSI_CSISR_EOF_INT_MASK)
#define CSI_CSISR_RxFF_INT_MASK                  (0x40000U)
#define CSI_CSISR_RxFF_INT_SHIFT                 (18U)
#define CSI_CSISR_RxFF_INT(x)                    (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_RxFF_INT_SHIFT)) & CSI_CSISR_RxFF_INT_MASK)
#define CSI_CSISR_DMA_TSF_DONE_FB1_MASK          (0x80000U)
#define CSI_CSISR_DMA_TSF_DONE_FB1_SHIFT         (19U)
#define CSI_CSISR_DMA_TSF_DONE_FB1(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DMA_TSF_DONE_FB1_SHIFT)) & CSI_CSISR_DMA_TSF_DONE_FB1_MASK)
#define CSI_CSISR_DMA_TSF_DONE_FB2_MASK          (0x100000U)
#define CSI_CSISR_DMA_TSF_DONE_FB2_SHIFT         (20U)
#define CSI_CSISR_DMA_TSF_DONE_FB2(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DMA_TSF_DONE_FB2_SHIFT)) & CSI_CSISR_DMA_TSF_DONE_FB2_MASK)
#define CSI_CSISR_STATFF_INT_MASK                (0x200000U)
#define CSI_CSISR_STATFF_INT_SHIFT               (21U)
#define CSI_CSISR_STATFF_INT(x)                  (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_STATFF_INT_SHIFT)) & CSI_CSISR_STATFF_INT_MASK)
#define CSI_CSISR_DMA_TSF_DONE_SFF_MASK          (0x400000U)
#define CSI_CSISR_DMA_TSF_DONE_SFF_SHIFT         (22U)
#define CSI_CSISR_DMA_TSF_DONE_SFF(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DMA_TSF_DONE_SFF_SHIFT)) & CSI_CSISR_DMA_TSF_DONE_SFF_MASK)
#define CSI_CSISR_RF_OR_INT_MASK                 (0x1000000U)
#define CSI_CSISR_RF_OR_INT_SHIFT                (24U)
#define CSI_CSISR_RF_OR_INT(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_RF_OR_INT_SHIFT)) & CSI_CSISR_RF_OR_INT_MASK)
#define CSI_CSISR_SF_OR_INT_MASK                 (0x2000000U)
#define CSI_CSISR_SF_OR_INT_SHIFT                (25U)
#define CSI_CSISR_SF_OR_INT(x)                   (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_SF_OR_INT_SHIFT)) & CSI_CSISR_SF_OR_INT_MASK)
#define CSI_CSISR_DMA_FIELD1_DONE_MASK           (0x4000000U)
#define CSI_CSISR_DMA_FIELD1_DONE_SHIFT          (26U)
#define CSI_CSISR_DMA_FIELD1_DONE(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DMA_FIELD1_DONE_SHIFT)) & CSI_CSISR_DMA_FIELD1_DONE_MASK)
#define CSI_CSISR_DMA_FIELD0_DONE_MASK           (0x8000000U)
#define CSI_CSISR_DMA_FIELD0_DONE_SHIFT          (27U)
#define CSI_CSISR_DMA_FIELD0_DONE(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_DMA_FIELD0_DONE_SHIFT)) & CSI_CSISR_DMA_FIELD0_DONE_MASK)
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR_MASK    (0x10000000U)
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR_SHIFT   (28U)
#define CSI_CSISR_BASEADDR_CHHANGE_ERROR(x)      (((uint32_t)(((uint32_t)(x)) << CSI_CSISR_BASEADDR_CHHANGE_ERROR_SHIFT)) & CSI_CSISR_BASEADDR_CHHANGE_ERROR_MASK)

/** \brief CSIDMASA_STATFIFO - CSI DMA Start Address Register - for STATFIFO */
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_MASK (0xFFFFFFFCU)
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT (2U)
#define CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF(x) (((uint32_t)(((uint32_t)(x)) << CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_SHIFT)) & CSI_CSIDMASA_STATFIFO_DMA_START_ADDR_SFF_MASK)

/** \brief CSIDMATS_STATFIFO - CSI DMA Transfer Size Register - for STATFIFO */
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK (0xFFFFFFFFU)
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT (0U)
#define CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF(x) (((uint32_t)(((uint32_t)(x)) << CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_SHIFT)) & CSI_CSIDMATS_STATFIFO_DMA_TSF_SIZE_SFF_MASK)

/** \brief CSIDMASA_FB1 - CSI DMA Start Address Register - for Frame Buffer1 */
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_MASK (0xFFFFFFFCU)
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_SHIFT (2U)
#define CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1(x)   (((uint32_t)(((uint32_t)(x)) << CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_SHIFT)) & CSI_CSIDMASA_FB1_DMA_START_ADDR_FB1_MASK)

/** \brief CSIDMASA_FB2 - CSI DMA Transfer Size Register - for Frame Buffer2 */
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_MASK (0xFFFFFFFCU)
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_SHIFT (2U)
#define CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2(x)   (((uint32_t)(((uint32_t)(x)) << CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_SHIFT)) & CSI_CSIDMASA_FB2_DMA_START_ADDR_FB2_MASK)

/** \brief CSIFBUF_PARA - CSI Frame Buffer Parameter Register */
#define CSI_CSIFBUF_PARA_FBUF_STRIDE_MASK        (0xFFFFU)
#define CSI_CSIFBUF_PARA_FBUF_STRIDE_SHIFT       (0U)
#define CSI_CSIFBUF_PARA_FBUF_STRIDE(x)          (((uint32_t)(((uint32_t)(x)) << CSI_CSIFBUF_PARA_FBUF_STRIDE_SHIFT)) & CSI_CSIFBUF_PARA_FBUF_STRIDE_MASK)
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_MASK (0xFFFF0000U)
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_SHIFT (16U)
#define CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE(x)   (((uint32_t)(((uint32_t)(x)) << CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_SHIFT)) & CSI_CSIFBUF_PARA_DEINTERLACE_STRIDE_MASK)

/** \brief CSIIMAG_PARA - CSI Image Parameter Register */
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT_MASK       (0xFFFFU)
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT_SHIFT      (0U)
#define CSI_CSIIMAG_PARA_IMAGE_HEIGHT(x)         (((uint32_t)(((uint32_t)(x)) << CSI_CSIIMAG_PARA_IMAGE_HEIGHT_SHIFT)) & CSI_CSIIMAG_PARA_IMAGE_HEIGHT_MASK)
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH_MASK        (0xFFFF0000U)
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH_SHIFT       (16U)
#define CSI_CSIIMAG_PARA_IMAGE_WIDTH(x)          (((uint32_t)(((uint32_t)(x)) << CSI_CSIIMAG_PARA_IMAGE_WIDTH_SHIFT)) & CSI_CSIIMAG_PARA_IMAGE_WIDTH_MASK)

/** \brief CSICR18 - CSI Control Register 18 */
#define CSI_CSICR18_DEINTERLACE_EN_MASK          (0x4U)
#define CSI_CSICR18_DEINTERLACE_EN_SHIFT         (2U)
#define CSI_CSICR18_DEINTERLACE_EN(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_DEINTERLACE_EN_SHIFT)) & CSI_CSICR18_DEINTERLACE_EN_MASK)
#define CSI_CSICR18_PARALLEL24_EN_MASK           (0x8U)
#define CSI_CSICR18_PARALLEL24_EN_SHIFT          (3U)
#define CSI_CSICR18_PARALLEL24_EN(x)             (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_PARALLEL24_EN_SHIFT)) & CSI_CSICR18_PARALLEL24_EN_MASK)
#define CSI_CSICR18_BASEADDR_SWITCH_EN_MASK      (0x10U)
#define CSI_CSICR18_BASEADDR_SWITCH_EN_SHIFT     (4U)
#define CSI_CSICR18_BASEADDR_SWITCH_EN(x)        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_BASEADDR_SWITCH_EN_SHIFT)) & CSI_CSICR18_BASEADDR_SWITCH_EN_MASK)
#define CSI_CSICR18_BASEADDR_SWITCH_SEL_MASK     (0x20U)
#define CSI_CSICR18_BASEADDR_SWITCH_SEL_SHIFT    (5U)
#define CSI_CSICR18_BASEADDR_SWITCH_SEL(x)       (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_BASEADDR_SWITCH_SEL_SHIFT)) & CSI_CSICR18_BASEADDR_SWITCH_SEL_MASK)
#define CSI_CSICR18_FIELD0_DONE_IE_MASK          (0x40U)
#define CSI_CSICR18_FIELD0_DONE_IE_SHIFT         (6U)
#define CSI_CSICR18_FIELD0_DONE_IE(x)            (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_FIELD0_DONE_IE_SHIFT)) & CSI_CSICR18_FIELD0_DONE_IE_MASK)
#define CSI_CSICR18_DMA_FIELD1_DONE_IE_MASK      (0x80U)
#define CSI_CSICR18_DMA_FIELD1_DONE_IE_SHIFT     (7U)
#define CSI_CSICR18_DMA_FIELD1_DONE_IE(x)        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_DMA_FIELD1_DONE_IE_SHIFT)) & CSI_CSICR18_DMA_FIELD1_DONE_IE_MASK)
#define CSI_CSICR18_LAST_DMA_REQ_SEL_MASK        (0x100U)
#define CSI_CSICR18_LAST_DMA_REQ_SEL_SHIFT       (8U)
#define CSI_CSICR18_LAST_DMA_REQ_SEL(x)          (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_LAST_DMA_REQ_SEL_SHIFT)) & CSI_CSICR18_LAST_DMA_REQ_SEL_MASK)
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_MASK (0x200U)
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_SHIFT (9U)
#define CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE(x)  (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_SHIFT)) & CSI_CSICR18_BASEADDR_CHANGE_ERROR_IE_MASK)
#define CSI_CSICR18_RGB888A_FORMAT_SEL_MASK      (0x400U)
#define CSI_CSICR18_RGB888A_FORMAT_SEL_SHIFT     (10U)
#define CSI_CSICR18_RGB888A_FORMAT_SEL(x)        (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_RGB888A_FORMAT_SEL_SHIFT)) & CSI_CSICR18_RGB888A_FORMAT_SEL_MASK)
#define CSI_CSICR18_AHB_HPROT_MASK               (0xF000U)
#define CSI_CSICR18_AHB_HPROT_SHIFT              (12U)
#define CSI_CSICR18_AHB_HPROT(x)                 (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_AHB_HPROT_SHIFT)) & CSI_CSICR18_AHB_HPROT_MASK)
#define CSI_CSICR18_MASK_OPTION_MASK             (0xC0000U)
#define CSI_CSICR18_MASK_OPTION_SHIFT            (18U)
#define CSI_CSICR18_MASK_OPTION(x)               (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_MASK_OPTION_SHIFT)) & CSI_CSICR18_MASK_OPTION_MASK)
#define CSI_CSICR18_CSI_ENABLE_MASK              (0x80000000U)
#define CSI_CSICR18_CSI_ENABLE_SHIFT             (31U)
#define CSI_CSICR18_CSI_ENABLE(x)                (((uint32_t)(((uint32_t)(x)) << CSI_CSICR18_CSI_ENABLE_SHIFT)) & CSI_CSICR18_CSI_ENABLE_MASK)

/** \brief CSICR19 - CSI Control Register 19 */
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK (0xFFU)
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT (0U)
#define CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL(x) (((uint32_t)(((uint32_t)(x)) << CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_SHIFT)) & CSI_CSICR19_DMA_RFIFO_HIGHEST_FIFO_LEVEL_MASK)


/* end of group CSI_Register_Masks */


/*
 * The interrupt enable bits are in registers CSICR1[16:31], CSICR3[0:7],
 * and CSICR18[2:9]. So merge them into an uint32_t value, place CSICR18 control
 * bits to [8:15].
 */
#define CSI_CSICR1_INT_EN_MASK 0xFFFF0000U
#define CSI_CSICR3_INT_EN_MASK 0x000000FFU
#define CSI_CSICR18_INT_EN_MASK 0x0000FF00U


/** \brief CSI - Register Layout Typedef */
typedef struct {
  volatile uint32_t CSICR1;                            /**< CSI Control Register 1, offset: 0x0 */
  volatile uint32_t CSICR2;                            /**< CSI Control Register 2, offset: 0x4 */
  volatile uint32_t CSICR3;                            /**< CSI Control Register 3, offset: 0x8 */
  volatile uint32_t CSISTATFIFO;                       /**< CSI Statistic FIFO Register, offset: 0xC */
  volatile uint32_t CSIRFIFO;                          /**< CSI RX FIFO Register, offset: 0x10 */
  volatile uint32_t CSIRXCNT;                          /**< CSI RX Count Register, offset: 0x14 */
  volatile uint32_t CSISR;                             /**< CSI Status Register, offset: 0x18 */
           uint8_t RESERVED_0[4];
  volatile uint32_t CSIDMASA_STATFIFO;                 /**< CSI DMA Start Address Register - for STATFIFO, offset: 0x20 */
  volatile uint32_t CSIDMATS_STATFIFO;                 /**< CSI DMA Transfer Size Register - for STATFIFO, offset: 0x24 */
  volatile uint32_t CSIDMASA_FB1;                      /**< CSI DMA Start Address Register - for Frame Buffer1, offset: 0x28 */
  volatile uint32_t CSIDMASA_FB2;                      /**< CSI DMA Transfer Size Register - for Frame Buffer2, offset: 0x2C */
  volatile uint32_t CSIFBUF_PARA;                      /**< CSI Frame Buffer Parameter Register, offset: 0x30 */
  volatile uint32_t CSIIMAG_PARA;                      /**< CSI Image Parameter Register, offset: 0x34 */
           uint8_t RESERVED_1[16];
  volatile uint32_t CSICR18;                           /**< CSI Control Register 18, offset: 0x48 */
  volatile uint32_t CSICR19;                           /**< CSI Control Register 19, offset: 0x4C */
} awbl_imx1050_reg_t;


/** \brief Camera interface type. */
typedef enum csi_interface
{
    GATED_CLOCK,    /**< \brief HSYNC/HREF, VSYNC, and PIXCLK signals are used. */
    NONGATED_CLOCK, /**< \brief VSYNC, and PIXCLK signals are used. */
    CCIR656,        /**< \brief CCIR656 interface. */
    MIPI,           /**< \brief MIPI CSI2 interface. */
} csi_interface_t;


enum use_ext_vsync_flags {
    NON_USE_EXT_VSYNC,
    USE_EXT_VSYNC,
};

typedef struct awbl_imx1050_csi_devinfo {

   uint8_t          camera_bus_id;
   uint32_t         regbase;            /**< \brief 寄存器基地址 */
   int              inum;               /**< \brief 中断号 */

   uint32_t         task_prio;    /**< \brief 传输任务优先级 */

   /** \brief 平台相关初始化：开启时钟、初始化引脚等操作 */
   void (*pfunc_plfm_init)(void);

} awbl_imx1050_csi_devinfo_t;


/**
 * \brief iMX RT1050 csi 设备实例
 */
typedef struct awbl_imx1050_csi_dev {

    struct awbl_dev         super;             /**< \brief 继承自 AWBus 设备 */

    /** \brief 摄像头控制器服务     */
    struct awbl_camera_controller_service   camera_controller_serv;

    /** \brief 摄像头控制器配制信息     */
    struct awbl_camera_controller_cfg_info  camera_controller_cfg_info;

    struct aw_list_head full_bufs_head;    /**< \brief video 模式下的满buffer链表头 */

    struct aw_list_head empty_bufs_head;   /**< \brief video 模式下的空buffer链表头  */

    uint32_t   *p_buf_nodes;             /**< \brief 用于保存动态申请的节点指针   */

    uint32_t   *p_video_buf_addr;          /**< \brief 用于保存动态申请的videobuffer的首地址  */

    uint32_t   *p_photo_buf_addr;          /**< \brief用于保存动态申请的photobuffer的首地址  */

    uint8_t     video_buf_num;             /**< \brief 传入的video buffer数量  */

    uint8_t     full_buf_num;              /**< \brief video 模式下，当前满链表buffer数量   */

    uint8_t     user_geted_buf_num;        /**< \brief 用户取走的buffer 个数  */

    uint8_t     bytes_per_pix;             /**< \brief 一个像素多少字节  */

    uint32_t    *p_photo_buff;             /**< \brief 存储的一帧照片的buffer的buffer */

    uint32_t     resolution;               /**< \brief 存储当前的分辨率  */

    current_mode_t current_mode;           /**< \brief 拍照模式，还是预模式  */

    uint8_t active_buf_num;                /**< \brief 当前活跃的buffer数量,最大为2 */

    uint8_t next_buf_idx;                  /**< \brief 交换FB1 和 FB2的索引  */

    AW_MUTEX_DECL(dev_lock);               /**< \brief 设备锁 */

    /** \brief 用于同步csi处理任务的信号量 */
    AW_SEMB_DECL(csi_sem_sync);

    /** \brief 用于计录前有多少个满buffer的信号量 */
    AW_SEMC_DECL(full_buffer_sem_sync);

    /** \brief 用于同步获取photo的信号量 */
    AW_SEMB_DECL(photo_sem_sync);

    /** \brief csi任务 */
    AW_TASK_DECL(csi_task_decl, __IMX1050_CSI_TASK_STACK_SIZE);

} awbl_imx1050_csi_dev_t;


/** \brief 存储buffer的节点  */
typedef struct __buffer_node {

    struct aw_list_head node;

    void         *p_buf;
}buffer_node_t;

void awbl_imx1050_csi_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX1050_CSI_H */

/* end of file */


