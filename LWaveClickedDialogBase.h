#pragma once

#include <QWidget>
#include"LAppCommom.h"
namespace Ui {
class LWaveClickedDialogBase;
}

class LWaveClickedDialogBase : public QWidget
{
    Q_OBJECT

public:
    explicit LWaveClickedDialogBase(QWidget *parent = 0);
    ~LWaveClickedDialogBase();
public:
    void  setCurrentWdt(WAVE_CLICKED_TYPE type);
private:
    Ui::LWaveClickedDialogBase *ui;
};


