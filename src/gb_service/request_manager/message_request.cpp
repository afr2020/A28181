/*
**	********************************************************************************
**
**	File		: message_request.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include <iostream>
#include "message_request.h"

namespace Zilu {
namespace Protocol {
namespace GB28181 {

int CKeepaliveRequest::HandleResponse(int statcode)
{
    std::cout << "Keepalive: "<<  m_reqid<<", statcode: " << statcode << endl;
    m_statcode = statcode;
    onRequestFinished();

    return 0;
}

int CKeepaliveRequest::GetStatCode()
{
    return m_statcode;
}

}
}
}
