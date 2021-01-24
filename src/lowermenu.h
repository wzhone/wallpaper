#ifndef LOWERMENU_H
#define LOWERMENU_H

#include <QWidget>

namespace Ui {
class LowerMenu;
}
class MainOperate;

class LowerMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LowerMenu(MainOperate *main);
    ~LowerMenu();

protected:
    void showEvent(QShowEvent *event);
    void changeEvent(QEvent * event);

private slots:
    void on_exit_clicked();

private:
    Ui::LowerMenu *ui;
    MainOperate* main;
};

#endif // LOWERMENU_H
