/*
**	********************************************************************************
**
**	File		: gb28181_svr_manager.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include <iostream>

#include <gb_service/request_manager/request_manager.h>
#include <media_transpond/session_manager.h>
#include "gb28181_svr_manager.h"
#include "config_manager.h"
#include "sip_server.h"
#include "media_transpond/defs.h"

namespace Zilu {
namespace Protocol {
namespace GB28181 {

std::string g_sipfrom_ipport;
std::string g_sipfrom_domain;

std::string g_sipproxy_ipport;
std::string g_sipproxy_domain;

eXosip_t *g_excontext;

CGB28181SvrManager *CGB28181SvrManager::instance()
{
    static CGB28181SvrManager _ins;
    return &_ins;
}

CGB28181SvrManager::CGB28181SvrManager() : m_bRegok(false), m_heartbeat("gb_heartbeat")
{

}

CGB28181SvrManager::~CGB28181SvrManager()
{

}

int CGB28181SvrManager::Init()
{
    CConfigManager::instance()->GetLocalSip(m_localsipcfg);
    CConfigManager::instance()->GetRemoteSip(m_remotesipcfg);

    char sipfrom[128] = {0};
    snprintf(sipfrom, sizeof(sipfrom), "sip:%s@%s:%d", m_localsipcfg.svr_id.c_str(),
             m_localsipcfg.svr_ip.c_str(), m_localsipcfg.svr_port);
    g_sipfrom_ipport = sipfrom;
    g_sipfrom_domain = "sip:" + m_localsipcfg.svr_id + "@" + m_localsipcfg.svr_domain;

    char sipproxy[128] = {0};
    snprintf(sipproxy, sizeof(sipproxy), "sip:%s@%s:%d", m_remotesipcfg.svr_id.c_str(),
            m_remotesipcfg.svr_ip.c_str(), m_remotesipcfg.svr_port);
    g_sipproxy_ipport = sipproxy;
    g_sipproxy_domain = "sip:"+m_remotesipcfg.svr_id + "@" + m_remotesipcfg.svr_domain;

	printf("sipfrom %s,sipproxy %s\n",sipfrom,sipproxy);

    return 0;
}

int CGB28181SvrManager::Start()
{
	printf("CGB28181SvrManager::Start() enter\n");

	CSipServer* pServer = CSipServer::instance();
	printf("pServer %p\n",&pServer);

    CSipServer::instance()->Init();
    CSipServer::instance()->SetLocalConfig(m_localsipcfg.svr_id, m_localsipcfg.svr_ip, m_localsipcfg.svr_port);
    CSipServer::instance()->Start("Protocol/1.0");

    g_excontext = CSipServer::instance()->GetExosipContext();

    CRequestManager::instance()->Start();

    register_online();

    //��������
    Infra::thread_proc_t proc = bind(&CGB28181SvrManager::heartbeat_proc, this, std::placeholders::_1);
    m_heartbeat.Start(proc);

	printf("CGB28181SvrManager::Start()\n");
    return 0;
}

int CGB28181SvrManager::register_online()
{
    m_msgsender.RegisterOnline(m_remotesipcfg);
    return 0;
}

int CGB28181SvrManager::OnRegisterSuccess(int rid)
{
    std::cout << "rid: " << rid << " register success!" << endl;
    m_bRegok = true;
    return 0;
}

void CGB28181SvrManager::heartbeat_proc(void *param)
{
    std::cout << "heartbead thread entry." <<endl;

    int timeoutcnt = 0;     ///<��ʱ3��δ�ظ� ����ע��

    while (m_heartbeat.Looping())
    {
        if (m_bRegok) {
            if (0 != keepalive()) {
                timeoutcnt++;
            }
            if (timeoutcnt >= 3) {
                m_bRegok = false;
				std::cout << "keepalive failed 3." <<endl;
            }
        }
        else {
            register_online();
        }
        m_heartbeat.Sleep(50 * 1000);
    }
}

int CGB28181SvrManager::keepalive()
{
    CBaseRequestSPtr request;
    int r = m_msgsender.Keepalive(m_remotesipcfg, m_localsipcfg, true, request);
    if (r != 0) {
        return -1;
    }
    std::cout << "keepalive wait result."<<endl;
    request->WaitResult();
    std::cout << "keepalive wait over."<<endl;
    auto keepalive_req = dynamic_cast<CKeepaliveRequest*>(request.get());
    r = keepalive_req->GetStatCode();
    return r == 200 ? 0 : -2;
}

int CGB28181SvrManager::HandleDeviceControl(manscdp_devicecontrol_subcmd_e cmd, string &devid,
                                            manscdp_switch_status_e onoff)
{
    return 0;
}

int CGB28181SvrManager::HandlePTZControl(control_cmd_t &ctrlcmd, string &devid)
{
    return 0;
}

int CGB28181SvrManager::HandleMediaRequest(const sdp_description_t &req_sdp, const sip_event_sptr &e)
{
    const string& devid = req_sdp.u_uri;
    session_ptr s;
    CSessionManager::instance()->CreateSession(req_sdp.o_sessid, s);
    s->cid = e->exevent->cid;
    s->did = e->exevent->did;
    s->devid = s->devid;

    return 0;
}

}
}
}
