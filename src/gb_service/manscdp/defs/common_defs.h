/*
**	********************************************************************************
**
**	File		: common_defs.h
**	Description	: 
**	Modify		: 2020/3/3		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "types.h"
using namespace std;

namespace Zilu {
namespace Protocol {
namespace GB28181 {

struct common_item_t
{
    string      cmdtype;
    string      sn;
    string      devid;
};

///< ͨ��Ӧ���ʽ
///< Broadcast��DeviceConfig��Catalog(Ŀ¼�յ�Ӧ��)��Alarm��DeviceControl
struct common_answer_t : public common_item_t
{
    result_type_e   result;
};

struct manscdp_basicparam_cfg_t
{
    uint32_t    expire;
    uint32_t    heartbeat_interval;
    uint32_t    heartbeat_cnt;
    string      devname;
};

}
}
}
