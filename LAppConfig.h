/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 软件配置类，单例类，用于加载配置文件，或者后期用于实现登入验证                        *
* start date:  2020-8-31                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
class LAppConfig
{
public:
   static LAppConfig &GetInstance();
   void printData();
private:
    LAppConfig();
    LAppConfig(const LAppConfig&);// 禁止拷贝构造
    LAppConfig &operator=(const LAppConfig&);// 禁止复制构造
    static LAppConfig  m_Instance;
};

