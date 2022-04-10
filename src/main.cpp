/*
**	********************************************************************************
**
**	File		: main.cpp
**	Description	: 
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/
#include "gb_service/gb28181_svr_manager.h"
#include "config_manager.h"
#include "Infra/thread_pool.h"
#include "Infra/print_log.h"
#include <unistd.h>

using namespace Zilu;
using namespace Protocol;

void show_usage(char* argv)
{
    printf("Usage:\n");
    printf("   %s -c config_path\n\n", argv);
}

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        show_usage(argv[0]);
        return 0;
    }
    std::string argv1(argv[1]);
    if (argv1 != "-c")
    {
        show_usage(argv[0]);
        return 0;
    }

    //��ʼ��ȫ������
    std::string path = argv[2];
    CConfigManager::instance()->Load(path.c_str());

    log_config_t log;
    CConfigManager::instance()->GetLogConfig(log);


    if (log.enable)
    {
        //Infra::setLogLevel(log.level);
        //Infra::setLogPath(log.path.c_str(), log.logName.c_str());
    }
	
	printf("enter main loop1:\n");

    ///��ʼ��
    Infra::CThreadPool::instance()->Start(4);
    GB28181::CGB28181SvrManager::instance()->Init();
    GB28181::CGB28181SvrManager::instance()->Start();

	printf("enter main loop:\n");
	
    while (1) {
        usleep(2*1000);
    }

    return 0;
}
