#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>

namespace Ui {
class sign_in;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::sign_in *ui;
};

#endif // SIGN_IN_H
