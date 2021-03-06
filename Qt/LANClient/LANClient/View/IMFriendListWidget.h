#ifndef IMFRIENDLISTWIDGET_H
#define IMFRIENDLISTWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QScrollArea;
class QMenu;
class IMMainWidget;

class IMFriendListWidget : public QWidget
{
    Q_OBJECT
public:
    IMFriendListWidget(IMMainWidget *mainWidget, QWidget *parent = nullptr);
    void addItem(QWidget *item);

    //创建右键菜单
    void creatMenu();

signals:
    

public slots:
    void showMenu();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    QVBoxLayout *m_layout;
    QWidget *m_contentsWidget;
    QScrollArea *m_friendsScrollArea;

    //右键菜单
    QMenu *m_menu;

    IMMainWidget *m_mainWidget;
};

#endif // IMFRIENDLISTWIDGET_H
