#include "LConfirmDialog.h"
#include "ui_LConfirmDialog.h"

LConfirmDialog::LConfirmDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LConfirmDialog)
{
    ui->setupUi(this);
    this->hide();

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setWindowModality(Qt::WindowModal);
    connect(ui->confirmBtn,SIGNAL(clicked(bool)),this,SLOT(SlotConfirmBtnClicked()));
    connect(ui->cancleBtn,SIGNAL(clicked(bool)),this,SLOT(SlotCancleBtnClicked()));
}

LConfirmDialog::~LConfirmDialog()
{
    delete ui;
}

void LConfirmDialog::SlotConfirmBtnClicked()
{

    emit SigIfClearMeasureData(true);
    this->hide();
}

void LConfirmDialog::SlotCancleBtnClicked()
{
    emit SigIfClearMeasureData(false);
    this->hide();
}
