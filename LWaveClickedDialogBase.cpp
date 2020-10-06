#include "LWaveClickedDialogBase.h"
#include "ui_LWaveClickedDialogBase.h"

LWaveClickedDialogBase::LWaveClickedDialogBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LWaveClickedDialogBase)
{
    ui->setupUi(this);
}

LWaveClickedDialogBase::~LWaveClickedDialogBase()
{
    delete ui;
}

void LWaveClickedDialogBase::setCurrentWdt(WAVE_CLICKED_TYPE type)
{
    if(type == SPO2A_WAVE_CLICKED)
    {
      ui->stackedWidget->setCurrentWidget(ui->spo2AClickedWidget);
    }
    else if(type == SPO2B_WAVE_CLICKED)
    {
      ui->stackedWidget->setCurrentWidget(ui->spo2BClickedWidget);
    }
    else if(type == CO2_WAVE_CLICKED)
    ui->stackedWidget->setCurrentWidget(ui->co2ClickedWidget);
}
