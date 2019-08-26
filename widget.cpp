#include "widget.h"
#include <QFile>
#include <QDebug>


Widget::Widget(QWidget *parent) : QWidget(parent)
{

    v_layout = new QVBoxLayout(this);

    f_layout = new QFormLayout;
    pn_line_edit = new QLineEdit("XC7A200T-2FBG484I");
    in_line_edit = new QLineEdit("flight_time.csv");
    out_line_edit = new QLineEdit("PinPkgDelays.txt");
    go_button = new QPushButton("GO!");
    text_edit = new QTextEdit;

    f_layout->addRow("Part Number:", pn_line_edit);
    f_layout->addRow("CSV file:", in_line_edit);
    f_layout->addRow("Output:", out_line_edit);

    v_layout->addLayout(f_layout);
    v_layout->addWidget(go_button);
    go_button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    v_layout->addWidget(text_edit);

    this->setLayout(v_layout);
    this->setGeometry(500,500,700,500);

    connect(go_button,SIGNAL(clicked()),this,SLOT(process()));

}

void Widget::process(){

    QFile in_file(in_line_edit->text());
    QFile out_file(out_line_edit->text());    

    if (!in_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //сообщение об ошибке чтения файла
        text_edit->append("Ошибка чтения входного файла!");
    }    
    else if (!out_file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //сообщение об ошибке записи файла
        text_edit->append("Ошибка записи PinPkgDelays.txt!");
    }
    else {
        text_edit->append("Создание файла...");
        out_file.write("UNITS ps\n\n");
        out_file.write("PART_NUMBER " + pn_line_edit->text().toUtf8() + "\n");
        text_edit->append("...");
        QString line = "";
        QStringList items;

        while(!in_file.atEnd()) {
            line = in_file.readLine().trimmed();
            items = line.split(',');
            if (items.size()>4){
                out_file.write(items.at(1).toUtf8() + " " + items.at(4).toUtf8() + "\n");                
            }
        }

        in_file.close();
        out_file.close();
        text_edit->append("Готово.");
    }

}

Widget::~Widget(){

}
