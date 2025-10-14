#ifndef COCINA_H
#define COCINA_H

#include <QDialog>

namespace Ui {
class cocina;
}

class cocina : public QDialog
{
    Q_OBJECT

public:
    explicit cocina(QWidget *parent = nullptr);
    ~cocina();

private:
    Ui::cocina *ui;
};

#endif // COCINA_H
