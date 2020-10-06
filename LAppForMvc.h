#pragma once
#include<QWidget>
#include<QTableView>
#include<QStandardItemModel>
#include<QItemDelegate>
// 点击编辑框弹出下拉日历选择

class DateDelegate : public QItemDelegate
{
    Q_OBJECT
  public:
     DateDelegate(QObject * parent = 0);
     QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
     void setEditorData(QWidget*editor,const QModelIndex &index) const;
     void setModelData(QWidget*editor,QAbstractItemModel*model,const QModelIndex &index) const;
     void updateEditorGeometry(QWidget*editor,const QStyleOptionViewItem & option,const QModelIndex &index) const;

};
// 双击编辑框弹出职业选择
class ComboxDelegate:public QItemDelegate
{
   Q_OBJECT
public:
   ComboxDelegate(QObject*parent = 0);
   QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   void setEditorData(QWidget*editor,const QModelIndex &index) const;
   void setModelData(QWidget*editor,QAbstractItemModel*model,const QModelIndex &index) const;
   void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const;


};
// 双击实现收入范围选择
class SpinDelegate:public QItemDelegate
{
  Q_OBJECT
public:
    SpinDelegate(QObject * parent = 0);
    QWidget*createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget*editor,const QModelIndex &index) const;
    void setModelData(QWidget*editor,QAbstractItemModel*model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const;

};
// 创建视图，并读取配置文件
class LAppForMvc
{
public:
    LAppForMvc();
     ~LAppForMvc();
    void initMcvInfo();
    void setViewParent(QWidget*w);
private:
    QTableView *m_tableView;
    QStandardItemModel *m_model;
    DateDelegate *m_date;
    ComboxDelegate *m_combox;
    SpinDelegate *m_spin;
};

