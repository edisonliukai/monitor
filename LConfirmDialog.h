#ifndef LCONFIRMDIALOG_H
#define LCONFIRMDIALOG_H

#include <QWidget>

namespace Ui {
class LConfirmDialog;
}

class LConfirmDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LConfirmDialog(QWidget *parent = 0);
    ~LConfirmDialog();
signals:
    void SigIfClearMeasureData(bool);
public slots:
    void SlotConfirmBtnClicked();
    void SlotCancleBtnClicked();
private:
    Ui::LConfirmDialog *ui;
};

#endif // LCONFIRMDIALOG_H
