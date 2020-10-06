#include "LAppForMvc.h"
#include<QDebug>
#include<QTextCodec>
#include<QFile>
#include<QDateTimeEdit>
#include<QDate>
#include<QObject>
#include<QComboBox>
#include<QSpinBox>
/***********日历选择下拉框********************/
DateDelegate::DateDelegate(QObject *parent):QItemDelegate(parent)
{
 // do no thing
}

QWidget*DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    editor->installEventFilter(const_cast<DateDelegate*>(this));
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString datestr = index.model()->data(index).toString();
    QDate date = QDate::fromString(datestr,Qt::ISODate);
    QDateTimeEdit *edit = static_cast<QDateTimeEdit*>(editor);
    edit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateTimeEdit*edit = static_cast<QDateTimeEdit*>(editor);
    QDate date = edit->date();
    model->setData(index,QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

/******职业选择下拉框委托实现***************/
ComboxDelegate::ComboxDelegate(QObject *parent):QItemDelegate(parent)
{

}

QWidget * ComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   QComboBox *editor = new QComboBox(parent);
   editor->addItem("工人");
   editor->addItem("农民");
   editor->addItem("老师");
   editor->addItem("医生");
   editor->addItem("律师");
   editor->addItem("军人");
   editor->installEventFilter(const_cast<ComboxDelegate*>(this));
   return editor;
}

void ComboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();
    QComboBox *box = static_cast<QComboBox*>(editor);
    int i = box->findText(str);
    box->setCurrentIndex(i);
}

void ComboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox*>(editor);
    QString str = box->currentText();
    model->setData(index,str);

}

void ComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   editor->setGeometry(option.rect);
}


/*********收入范围选择下拉框***************/
SpinDelegate::SpinDelegate(QObject * parent):QItemDelegate(parent)
{

}

QWidget* SpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(0,10000);
    editor->installEventFilter(const_cast<SpinDelegate*>(this));
    return editor;
}

void SpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index).toInt();
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    box->setValue(value);

}

void SpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    int value = box->value();
    model->setData(index,value);

}

void SpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
/******MVC初始化信息**********************/
LAppForMvc::LAppForMvc()
{
  m_tableView = new QTableView;
  m_model = new QStandardItemModel(4,4);
  m_date = new DateDelegate;
  m_combox = new ComboxDelegate;
  m_spin =  new SpinDelegate;
}

LAppForMvc::~LAppForMvc()
{
    if(m_tableView)
    {
      delete  m_tableView;
        m_tableView = NULL;
    }

    if(m_model)
    {
        delete m_model;
        m_model = NULL;
    }
}
void LAppForMvc::setViewParent(QWidget *w)
{
    if(!w)
    {
        return;
    }
    if(m_tableView)
    {
        m_tableView->setParent(w);
    }
}

void LAppForMvc::initMcvInfo()
{
    if(!m_tableView)
    {
        return;
    }
    qDebug()<<"this is mvc";
    m_tableView->setFixedSize(450,200);

    m_tableView->setModel(m_model);
    m_tableView->setItemDelegateForColumn(1,m_date);
    m_tableView->setItemDelegateForColumn(2,m_combox);
    m_tableView->setItemDelegateForColumn(3,m_spin);
    m_model->setHeaderData(0,Qt::Horizontal,"姓名");
    m_model->setHeaderData(1,Qt::Horizontal,"生日");
    m_model->setHeaderData(2,Qt::Horizontal,"职业");
    m_model->setHeaderData(3,Qt::Horizontal,"收入");

    QTextCodec*code = QTextCodec::codecForName("utf8");
    QFile file(":/image/info.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&file);
        stream.setCodec(code);
        QString line;
        m_model->removeRows(0,m_model->rowCount(QModelIndex()),QModelIndex());
        int row = 0;
        do{
            line = stream.readLine();
            if(!line.isEmpty())
            {
                m_model->insertRows(row,1,QModelIndex());
                QStringList pieces = line.split(",",QString::SkipEmptyParts);
                m_model->setData(m_model->index(row,0,QModelIndex()),pieces.value(0));
                m_model->setData(m_model->index(row,1,QModelIndex()),pieces.value(1));
                m_model->setData(m_model->index(row,2,QModelIndex()),pieces.value(2));
                m_model->setData(m_model->index(row,3,QModelIndex()),pieces.value(3));
                qDebug()<<"row = "<<row;
                row++;
            }
        }while(!line.isEmpty());

       file.close();
    }
    m_tableView->setWindowTitle("mvc");
    m_tableView->show();
}
