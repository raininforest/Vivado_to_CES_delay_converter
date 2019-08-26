#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

class Widget : public QWidget
{
    Q_OBJECT

    QVBoxLayout* v_layout;
    QFormLayout* f_layout;

    QLineEdit* pn_line_edit;
    QLineEdit* csv_line_edit;
    QLineEdit* reg_exp_line_edit;
    QLineEdit* out_line_edit;

    QPushButton* go_button;
    QTextEdit* text_edit;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

signals:

public slots:

    void process();


};

#endif // WIDGET_H
