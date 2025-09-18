#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>

namespace Ui {
class sign_in;
}

class sign_in : public QWidget
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    ~sign_in();

private:
    Ui::sign_in *ui;
};

#endif // SIGN_IN_H
