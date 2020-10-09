#pragma once
// 在打印信息时会将信息所在的文件路径和代码行数显示出来
#define myPrintInfo qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

// 底部欄按鈕編號

enum BOTTOM_BUTTON_NO
{
  BOTTOM_BUTTON_START = 0,
  BOTTOM_BUTTON_MORE = BOTTOM_BUTTON_START,
  BOTTOM_BUTTON_ALARM_RESET,
  BOTTOM_BUTTON_ALARM_PASUE,
  BOTTOM_BUTTON_SCREEN,
  BOTTOM_BUTTON_PATENTION_INFO,
  BOTTOM_BUTTON_REVIEW,
  BOTTOM_BUTTON_STANDBY,
  BOTTOM_BUTTON_MAIN_MENU,
  BOTTOM_BUTTON_OTHER

};

// 生理指標項目

enum PHYSIOLOGICAL_INDEX
{
   PHYSIOLOGICAL_OF_START = 0,
   PHYSIOLOGICAL_OF_SPO2_A = PHYSIOLOGICAL_OF_START,
   PHYSIOLOGICAL_OF_SPO2_B,
   PHYSIOLOGICAL_OF_ECG,
   PHYSIOLOGICAL_OF_CO2
};

// 彈出框中的按鈕序號

enum MENU_BUTTON_ON
{
   MENU_BUTTON_START = 0,
   // 屏幕设置中的按钮
   MENU_BUTTON_BIG_SCREEN = MENU_BUTTON_START, //大字体界面
   MENU_BUTTON_NORMAL_SCREEN,     // 常规界面
   MENU_BUTTON_CCHD,              // CCHD筛选
   MENU_BUTTON_SINGLE_SPO2,       // 单血氧界面
   MENU_BUTTON_ECG,               // ECG界面
   MENU_BUTTON_CO2,               // CO2界面
   MENU_BUTTON_EXIT,              // 退出按钮

   // 主菜单中的按钮
   MENU_BUTTON_DEMO ,// 演示模式
   MENU_BUTTON_SCREEN_CHOICE,           // 屏幕选择
   MENU_BUTTON_PARAME_LAYOUT,           // 参数布局
   MENU_BUTTON_HOT_BUTTON,              // 热键
   MENU_BUTTON_SHOW,                    // 显示

   MENU_BUTTON_PRIVACY_MODE,            // 隐私模式
   MENU_BUTTON_NIGHT_MODE,              // 夜间模式
   MENU_BUTTON_ALARM_LIMIT,             // 报警
   MENU_BUTTON_INTUBATION_MODE,         // 插管模式
   MENU_BUTTON_RESCUE_MODE,             // 抢救模式

   MENU_BUTTON_EVENT,                   // 事件
   MENU_BUTTON_TEND_LIST,               // 趋势表
   MENU_BUTTON_TEND_MAP,                // 趋势图
   MENU_BUTTON_ALL_WAVE,                // 全息波形
   MENU_BUTTON_12_DAO,                  // 12导静息

   MENU_BUTTON_SET_CONFIG,              // 配置管理
   MENU_BUTTON_PATENTION_INFO,          // 病人信息
   MENU_BUTTON_RELASES_PATENTION,       // 解除病人
   MENU_BUTTON_HISTORY_PATENTION,       // 历史病人
   MENU_BUTTON_PATENTION_MANAGEMENT,    // 病人管理

   MENU_BUTTON_TIME,                    // 时间
   MENU_BUTTON_SYSTEM_VERSION,          // 系统版本
   MENU_BUTTON_MAINTAIN,                // 维护
   MENU_BUTTON_SOFTWARE_ABOUT,        // 关于我们
   MENU_BUTTON_SET_UP,                  // 设置

   MENU_BUTTON_DRUG,                    // 药物
   MENU_BUTTON_HEMODYNAMICS,            // 血液动力学
   MEUN_BUTTON_KIDNEY_FUNCTION,         // 肾功能
   MEUN_BUTTON_VENTILEACTION,           // 通气
   MEUN_BUTTON_OXYGENATION,             // 氧合
};

enum DRAW_WAVE_DIRCTION // 波形繪製方向
{
    DRAW_WAVE_FROM_RIGHT = 0,
    DRAW_WAVE_FROM_LEFT
};


enum WAVE_CLICKED_TYPE
{
  NO_WAVE_CLICKED = -1,
  SPO2A_WAVE_CLICKED ,
  SPO2B_WAVE_CLICKED,
  CO2_WAVE_CLICKED
};
