/*
**	********************************************************************************
**
**	File		: defs.h
**	Description	: 
**	Modify		: 2020/3/2		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <cstdint>

namespace Zilu {
namespace Protocol {

///< ��̨ ��ͷ�䱶
struct ptz_cmd_zoom_t
{
    enum cmd_type_e {
        ZOOM_UNKNOWN = 0,
        ZOOM_OUT,
        ZOOM_IN,
    };
    cmd_type_e  cmdtype;
    uint8_t     speed;
};

///< ��̨��ֱ�������
struct ptz_cmd_tilt_t
{
    enum cmd_type_e {
        TILT_UNKNOWN = 0,
        TILT_UP,
        TILT_DOWN,
    };
    cmd_type_e  cmdtype;
    uint8_t     speed;
};

///< ��̨ˮƽ���Ʒ���
struct ptz_cmd_pan_t
{
    enum cmd_type_e {
        PAN_UNKNOWN = 0,
        PAN_LEFT,
        PAN_RIGHT,
    };
    cmd_type_e  cmdtype;
    uint8_t     speed;
};

///< FIָ�� ��Ȧ
struct fi_cmd_iris_t
{
    enum cmd_type_e {
        IFIS_UNKNOWN = 0,
        IFIS_SHRINK,            ///<��С
        IFIS_AMPLIFICATION,     ///<�Ŵ�
    };
    cmd_type_e  cmdtype;
    uint8_t     speed;
};

///< FIָ�� �۽� ��Ȧ
struct fi_cmd_focus_t
{
    enum cmd_type_e {
        FOCUS_UNKNOWN = 0,
        FOCUS_NEAR,
        FOCUS_FAR,
    };
    cmd_type_e      cmdtype;
    uint8_t         speed;
};

///< Ԥ��λָ��
struct preset_cmd_t
{
    enum cmd_type_e {
        PRESET_UNKNOWN = 0,
        PRESET_SET,
        PRESET_CALL,
        PRESET_DELE
    };
    cmd_type_e  cmdtype;
    uint8_t     index;
};

///< Ѳ��ָ��
struct patrol_cmd_t
{
    enum cmd_type_e {
        PATROL_UNKNOWN = 0,
        PATROL_ADD,
        PATROL_DELE,
        PATROL_SET_SPEED,
        PATROL_SET_TIME,    ///<����ͣ��ʱ��
        PATROL_START,       ///<��ʼѲ��
        PATROL_STOP
    };
    cmd_type_e  cmdtype;
    uint8_t     patrol_id;      ///<Ѳ�����
    uint8_t     preset_id;      ///<Ԥ��λ��
    uint16_t    value;          ///<���ݣ��ٶȺ�ͣ��ʱ��ʹ��
};

///< �Զ�ɨ��ָ��
struct scan_cmd_t
{
    enum cmd_type_e {
        SCAN_UNKNOWN = 0,
        SCAN_START,
        SCAN_STOP,
        SCAN_SET_LEFT_BOADER,
        SCAN_SET_RIGHT_BOADER,
        SCAN_SET_SPEED
    };
    cmd_type_e  cmdtype;
    uint8_t     scan_id;
    uint16_t    speed;      ///< ����scan�ٶ�ʹ��
};

enum control_type_e
{
    CTRL_CMD_UNKNOWN = 0,
    PTZ_TYPE,       ///< PTZ����
    FI_TYPE,        ///<��Ȧ���۽�����
    PRESET_TYPE,    ///<Ԥ��λ
    PATROL_TYPE,    ///<Ѳ��
    SCAN_TYPE,      ///<ɨ��
    AUX_TYPE,       ///<��������

    CONTROL_STOP    ///<ֹͣ����
};

struct control_cmd_t
{
    uint8_t             first_byte;     ///< A5H
    uint8_t             version;        ///< �汾��
    uint8_t             check;          ///< У��λ

    control_type_e      ctrltype;

    struct {
        ptz_cmd_pan_t   ptz_pan;
        ptz_cmd_tilt_t  ptz_tilt;
        ptz_cmd_zoom_t  ptz_zoom;
    };

    struct {
        fi_cmd_focus_t  fi_focus;
        fi_cmd_iris_t   fi_iris;
    };

    preset_cmd_t        preset;

    patrol_cmd_t        patrol;

    scan_cmd_t          autoscan;
};

}
}
