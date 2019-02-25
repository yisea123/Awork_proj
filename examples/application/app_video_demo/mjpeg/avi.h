#ifndef __AVI_H
#define __AVI_H 

#include "stdint.h"


/**
 * \brief AVI��Ƶ�ļ���������ֵ
 */
typedef enum {
    AVI_OK = 0,           /**< \brief �ɹ� */
    AVI_RIFF_ERR,         /**< \brief RIFF ID��ȡʧ�� */
    AVI_AVI_ERR,          /**< \brief AVI ID��ȡʧ�� */
    AVI_LIST_ERR,         /**< \brief LIST ID��ȡʧ�� */
    AVI_HDRL_ERR,         /**< \brief HDRL ID��ȡʧ�� */
    AVI_AVIH_ERR,         /**< \brief AVIH ID��ȡʧ�� */
    AVI_STRL_ERR,         /**< \brief STRL ID��ȡʧ�� */
    AVI_STRH_ERR,         /**< \brief STRH ID��ȡʧ�� */
    AVI_STRF_ERR,         /**< \brief STRF ID��ȡʧ�� */
    AVI_MOVI_ERR,         /**< \brief MOVI ID��ȡʧ�� */
    AVI_FORMAT_ERR,       /**< \brief ��ʽ���� */
    AVI_STREAM_ERR,       /**< \brief ������ */
} avi_status_t;


#define AVI_RIFF_ID         0X46464952
#define AVI_AVI_ID          0X20495641
#define AVI_LIST_ID         0X5453494C
#define AVI_HDRL_ID         0X6C726468      /**< \brief ��Ϣ���־ */
#define AVI_MOVI_ID         0X69766F6D      /**< \brief ���ݿ��־ */
#define AVI_STRL_ID         0X6C727473      /**< \brief strl��־ */
#define AVI_AVIH_ID         0X68697661      /**< \brief avih�ӿ��AVI_HDRL_ID */
#define AVI_STRH_ID         0X68727473      /**< \brief strh(��ͷ)�ӿ��AVI_STRL_ID */
#define AVI_STRF_ID         0X66727473      /**< \brief strf(����ʽ)�ӿ��AVI_STRL_ID */
#define AVI_STRD_ID         0X64727473      /**< \brief strd�ӿ��AVI_STRL_ID (��ѡ��) */
#define AVI_VIDS_STREAM     0X73646976      /**< \brief ��Ƶ�� */
#define AVI_AUDS_STREAM     0X73647561      /**< \brief ��Ƶ�� */
#define AVI_VIDS_FLAG       0X6463          /**< \brief ��Ƶ����־ */
#define AVI_AUDS_FLAG       0X7762          /**< \brief ��Ƶ����־ */
#define AVI_FORMAT_MJPG     0X47504A4D

#pragma pack(push)
#pragma pack(1)


/**
 * \brief AVI��Ϣ�ṹ��
 */
typedef struct{

    uint32_t sec_per_frame;      /**< \brief ��Ƶ֡���ʱ��(��λΪus) */
    uint32_t total_frame;        /**< \brief �ļ���֡�� */
    uint32_t width;              /**< \brief ͼ��� */
    uint32_t height;             /**< \brief ͼ��� */
    uint32_t sample_rate;        /**< \brief ��Ƶ������ */
    uint16_t channels;           /**< \brief ������,һ��Ϊ2,��ʾ������ */
    uint16_t audio_buf_size;     /**< \brief ��Ƶ��������С */
    uint16_t audio_type;         /**< \brief ��Ƶ����:0X0001=PCM;0X0050=MP2;0X0055=MP3;0X2000=AC3; */
    uint16_t stream_id;          /**< \brief ������ID,StreamID=='dc'==0X6463 /StreamID=='wb'==0X7762 */
    uint32_t stream_size;        /**< \brief ����С,������ż��,�����ȡ��Ϊ����,���1.��Ϊż��. */
    uint8_t* video_flag;         /**< \brief ��Ƶ֡���,VideoFLAG="00dc"/"01dc" */
    uint8_t* audio_flag;         /**< \brief ��Ƶ֡���,AudioFLAG="00wb"/"01wb" */
} avi_info_t;

#pragma pack(pop)


/**
 * \brief AVI����Ϣ
 */
typedef struct {
    uint32_t riff_id;            /**< \brief RiffID=='RIFF'==0X61766968 */
    uint32_t file_size;          /**< \brief AVI�ļ���С(�����������8�ֽ�,ҲRIFFID��FileSize����������) */
    uint32_t avi_id;             /**< \brief AviID=='AVI '==0X41564920 */
} avi_header_t;


/**
 * \brief FRAME����Ϣ
 */
typedef struct {
    uint32_t frame_id;           /**< \brief ֡ID,FrameID=='RIFF'==0X61766968 */
    uint32_t frame_size;         /**< \brief ֡��С */
} frame_header_t;



/**
 * \brief LIST����Ϣ
 */
typedef struct {
    uint32_t list_id;             /**< \brief ListID=='LIST'==0X4c495354 */
    uint32_t block_size;          /**< \brief ���С(�����������8�ֽ�,ҲListID��BlockSize����������) */
    uint32_t list_type;           /**< \brief LIST�ӿ�����:hdrl(��Ϣ��)/movi(���ݿ�)/idxl(������,�Ǳ���,�ǿ�ѡ��) */
} list_header_t;

/**< \brief avih �ӿ���Ϣ */
typedef struct {
    uint32_t block_id;            /**< \brief ���־:avih==0X61766968 */
    uint32_t block_size;          /**< \brief ���С(�����������8�ֽ�,Ҳ����BlockID��BlockSize����������) */
    uint32_t sec_per_frame;       /**< \brief ��Ƶ֡���ʱ��(��λΪus) */
    uint32_t max_byte_sec;        /**< \brief ������ݴ�����,�ֽ�/�� */
    uint32_t padding_granularity; /**< \brief ������������ */
    uint32_t flags;               /**< \brief AVI�ļ���ȫ�ֱ�ǣ������Ƿ���������� */
    uint32_t total_frame;         /**< \brief �ļ���֡�� */
    uint32_t init_frames;         /**< \brief Ϊ������ʽָ����ʼ֡�����ǽ�����ʽӦ��ָ��Ϊ0�� */
    uint32_t streams;             /**< \brief �������������������,ͨ��Ϊ2 */
    uint32_t ref_buf_size;        /**< \brief �����ȡ���ļ��Ļ����С��Ӧ���������Ŀ飩Ĭ�Ͽ�����1M�ֽ�!!! */
    uint32_t width;               /**< \brief ͼ��� */
    uint32_t height;              /**< \brief ͼ��� */
    uint32_t reserved[4];         /**< \brief ���� */
} avih_header_t;

/**< \brief strh ��ͷ�ӿ���Ϣ(strh��strl) */
typedef struct {
    uint32_t block_id;            /**< \brief ���־:strh==0X73747268 */
    uint32_t block_size;          /**< \brief ���С(�����������8�ֽ�,Ҳ����BlockID��BlockSize����������) */
    uint32_t stream_type;         /**< \brief ���������࣬vids(0X73646976):��Ƶ;auds(0X73647561):��Ƶ */
    uint32_t handler;             /**< \brief ָ�����Ĵ����ߣ���������Ƶ��˵���ǽ�����,����MJPG/H264֮���. */
    uint32_t flags;               /**< \brief ��ǣ��Ƿ�����������������ɫ���Ƿ�仯�� */
    uint16_t priority;            /**< \brief �������ȼ������ж����ͬ���͵���ʱ���ȼ���ߵ�ΪĬ������ */
    uint16_t language;            /**< \brief ��Ƶ�����Դ��� */
    uint32_t init_frames;         /**< \brief Ϊ������ʽָ����ʼ֡�� */
    uint32_t scale;               /**< \brief ������, ��Ƶÿ��Ĵ�С������Ƶ�Ĳ�����С */
    uint32_t rate;                /**< \brief Scale/Rate=ÿ������� */
    uint32_t start;               /**< \brief ��������ʼ���ŵ�λ�ã���λΪScale */
    uint32_t length;              /**< \brief ������������������λΪScale */
    uint32_t ref_buf_size;        /**< \brief ����ʹ�õĻ�������С */
    uint32_t quality;             /**< \brief ��ѹ������������ֵԽ������Խ�� */
    uint32_t sampleSize;          /**< \brief ��Ƶ��������С */
    struct {                      /**< \brief ��Ƶ֡��ռ�ľ��� */

        short left;
        short top;
        short right;
        short bottom;
    } frame;
} strh_header_t;


/**
 * \brief BMP�ṹ��
 */
typedef struct {
    uint32_t  bmp_size;           /**< \brief bmp�ṹ���С,����(BmpSize����) */
    long      width;              /**< \brief ͼ��� */
    long      height;             /**< \brief ͼ��� */
    uint16_t  planes;             /**< \brief ƽ����������Ϊ1 */
    uint16_t  bit_count;          /**< \brief ����λ��,0X0018��ʾ24λ */
    uint32_t  compression;        /**< \brief ѹ�����ͣ�����:MJPG/H264�� */
    uint32_t  size_image;         /**< \brief ͼ���С */
    long      xpix_per_meter;     /**< \brief ˮƽ�ֱ��� */
    long      ypix_per_meter;     /**< \brief ��ֱ�ֱ��� */
    uint32_t  clr_used;           /**< \brief ʵ��ʹ���˵�ɫ���е���ɫ��,ѹ����ʽ�в�ʹ�� */
    uint32_t  clr_important;      /**< \brief ��Ҫ����ɫ */
} bmp_header_t;


/**
 * \brief ��ɫ��
 */
typedef struct {
    uint8_t  rgb_blue;            /**< \brief ��ɫ������(ֵ��ΧΪ0-255) */
    uint8_t  rgb_green;           /**< \brief ��ɫ������(ֵ��ΧΪ0-255) */
    uint8_t  rgb_red;             /**< \brief ��ɫ������(ֵ��ΧΪ0-255) */
    uint8_t  rgb_reserved;        /**< \brief ����������Ϊ0 */
} avi_rgb_quad_t;


/**
 * \brief ����strh,�������Ƶ��,strf(����ʽ)ʹSTRH_BMPHEADER��
 */
typedef struct  {
    uint32_t block_id;              /**< \brief ���־,strf==0X73747266 */
    uint32_t block_size;            /**< \brief ���С(�����������8�ֽ�,Ҳ����BlockID�ͱ�BlockSize����������) */
    bmp_header_t   bmp_header;      /**< \brief λͼ��Ϣͷ */
    avi_rgb_quad_t bmp_colors[1];   /**< \brief ��ɫ�� */
} strf_bmp_header_t;


/**
 * \brief ����strh,�������Ƶ��,strf(����ʽ)ʹSTRH_WAVHEADER��
 */
typedef struct 
{
    uint32_t block_id;             /**< \brief ���־,strf==0X73747266 */
    uint32_t block_size;           /**< \brief ���С(�����������8�ֽ�,Ҳ����BlockID�ͱ�BlockSize����������) */
    uint16_t format_tag;           /**< \brief ��ʽ��־:0X0001=PCM,0X0055=MP3... */
    uint16_t channels;             /**< \brief ������,һ��Ϊ2,��ʾ������ */
    uint32_t sample_rate;          /**< \brief ��Ƶ������ */
    uint32_t baud_rate;            /**< \brief ������ */
    uint16_t block_align;          /**< \brief ���ݿ�����־ */
    uint16_t size;                 /**< \brief �ýṹ��С */
} strf_wav_header_t;


/**
 * \brief  AVI��Ƶ�����ʼ��
 * \param[in]  p_buf   ���뻺����
 * \param[in]  size    �������Ĵ�С
 * \param[out] p_info  AVI��Ƶ��Ϣ
 *
 * \return avi_status_t��Ա
 *
 */
avi_status_t avi_init(uint8_t *p_buf, uint16_t size, avi_info_t *p_info);


/**
 * \brief ����ID (Ҫ���ҵ�ID������4�ֽڳ���)
 *
 * \param[in] p_buf  ���黺����
 * \param[in] size   �������Ĵ�С
 *
 * \retval  0   ����ʧ��
 *          >0  ID��ƫ����
 */
uint16_t avi_srarch_id (uint8_t *p_buf, uint16_t size, const char *id);


/**
 * \brief �õ�stream����Ϣ
 *
 * \param[in] p_buf        ����ʼ�ĵ�ַ
 * \param[out] stream_id   ��ID����
 * \param[out] stream_size ����С
 *
 * \return  avi_status_t��Ա
 *
 */
avi_status_t avi_get_streaminfo (uint8_t  *p_buf,
                                 uint16_t *stream_id,
                                 uint32_t *stream_size);


extern avi_info_t avix;       /**< \brief avi�ļ������Ϣ */


#endif

