//Basak Amasya
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>

//struct book is in the header file
QVector<book> books; //a global vector to keep all the books
QString type = "All";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("C:\\Users\\Lenovo\\Documents\\SABANCI\\CS204\\Bamasya_Amasya_Basak_hw9\\booklist.txt");//write your own file's path here
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "File cannot be found", file.errorString());
    }
    QTextStream infile(&file);

    while(!infile.atEnd())  //reading the file line by line
    {
        QString line = infile.readLine();
        QStringList fields = line.split(", ");
        book newbook; //creating a new book for each line
        newbook.name = fields[0];
        newbook.writer = fields[1];
        newbook.kind = fields[2];
        newbook.publisher = fields[3];
        newbook.stock = fields[4];
        books.push_back(newbook); //putting the book to the vector
    }
    file.close();
    int rowno = books.size();
    ui->tableWidget->setRowCount(rowno);

    for (int i = 0; i < books.size() ; i++) //creating the table for the books
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(books[i].name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(books[i].writer));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(books[i].kind));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(books[i].publisher));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(books[i].stock));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_clicked()
{
    type = "All";
    ui->tableWidget->clearContents();
    int rowno = books.size();
    ui->tableWidget->setRowCount(rowno);

    for (int i = 0; i < books.size() ; i++) //showing all the books from the vector
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(books[i].name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(books[i].writer));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(books[i].kind));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(books[i].publisher));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(books[i].stock));
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    type = "Poetry";
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    int count = 0;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].kind == "Poetry") //showing the book if the kind is poetry
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(books[i].name));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(books[i].writer));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(books[i].kind));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(books[i].publisher));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(books[i].stock));
            count ++;
        }
    }
}

void MainWindow::on_radioButton_3_clicked()
{
    type = "Novel";
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    int count = 0;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].kind == "Novel") //showing the book if the kind is novel
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(books[i].name));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(books[i].writer));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(books[i].kind));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(books[i].publisher));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(books[i].stock));
            count ++;
        }
    }
}

void MainWindow::on_radioButton_4_clicked()
{
    type = "Science";
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    int count = 0;
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].kind == "Science") //showing the book if the kind is science
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(books[i].name));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(books[i].writer));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(books[i].kind));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(books[i].publisher));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(books[i].stock));
            count ++;
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
   QVector<book> searchbooks; //keeping a vector for searching
   if (type == "All")
   {
        searchbooks = books;
        if (ui->lineEdit->text() != "") //if something is written for the writer
        {
            QString writername = ui->lineEdit->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = writername.length();
                if (len <= searchbooks[i].writer.length())
                {
                    QString writernamesub = searchbooks[i].writer.mid(0,len);
                    if (writernamesub != writername) //if that's not the writer name we are searching for
                    {
                        searchbooks.remove(i); //remove that book from the vector
                        i--;
                    }
                }
                else //if the length of the input is bigger that the writer name
                {
                    searchbooks.remove(i); //remove that book from the vector
                    i--;
                }
            }
        }
        if (ui->lineEdit_2->text() != "") //if something is written for the book name
        {
            QString bookname = ui->lineEdit_2->text();

            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = bookname.length();
                if (len <= searchbooks[i].name.length())
                {
                    QString booknamesub = searchbooks[i].name.mid(0,len);
                    if (booknamesub != bookname) //if that's not the book name we are searching for
                    {
                        searchbooks.remove(i); //remove that book from the vector
                        i--;
                    }
                }
                else  //if the length of the input is bigger that the writer name
                {
                    searchbooks.remove(i); //remove that book from the vector
                    i--;
                }
            }
        }
        if (ui->lineEdit_3->text() != "") //if something is written for the publisher
        {
            QString publishername = ui->lineEdit_3->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = publishername.length();
                if (len <= searchbooks[i].publisher.length())
                {
                    QString publishernamesub = searchbooks[i].publisher.mid(0,len);
                    if (publishernamesub != publishername) //if that's not the pubsliher we are searching for
                    {
                        searchbooks.remove(i); //remove that book from the vector
                        i--;
                    }

                }
                else  //if the length of the input is bigger that the writer name
                {
                    searchbooks.remove(i); //remove that book from the vector
                    i--;
                }
            }
        }
    }
   if (type == "Poetry")
    {
       for (int i = 0; i < books.size(); i++)
       {
           if (books[i].kind == "Poetry")
           {
               searchbooks.push_back(books[i]);
           }
       }
       if (ui->lineEdit->text() != "")
       {
           QString writername = ui->lineEdit->text();
           for (int i = 0; i < searchbooks.size(); i++)
           {
               int len = writername.length();
               if (len <= searchbooks[i].writer.length())
               {
                   QString writernamesub = searchbooks[i].writer.mid(0,len);
                   if (writernamesub != writername)
                   {
                       searchbooks.remove(i);
                       i--;
                   }
               }
               else{
                   searchbooks.remove(i);
                   i--;
               }
           }
       }
       if (ui->lineEdit_2->text() != "")
       {
           QString bookname = ui->lineEdit_2->text();

           for (int i = 0; i < searchbooks.size(); i++)
           {
               int len = bookname.length();
               if (len <= searchbooks[i].name.length())
               {
                   QString booknamesub = searchbooks[i].name.mid(0,len);
                   if (booknamesub != bookname)
                   {
                       searchbooks.remove(i);
                       i--;
                   }
               }
               else{
                   searchbooks.remove(i);
                   i--;
               }
           }
       }
       if (ui->lineEdit_3->text() != "")
       {
           QString publishername = ui->lineEdit_3->text();
           for (int i = 0; i < searchbooks.size(); i++)
           {
               int len = publishername.length();
               if (len <= searchbooks[i].publisher.length())
               {
                   QString publishernamesub = searchbooks[i].publisher.mid(0,len);
                   if (publishernamesub != publishername)
                   {
                       searchbooks.remove(i);
                       i--;
                   }

               }
               else{
                   searchbooks.remove(i);
                   i--;
               }
           }
       }

    }
   if (type == "Novel")
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].kind == "Novel")
            {
                searchbooks.push_back(books[i]);
            }
        }
        if (ui->lineEdit->text() != "")
        {
            QString writername = ui->lineEdit->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = writername.length();
                if (len <= searchbooks[i].writer.length())
                {
                    QString writernamesub = searchbooks[i].writer.mid(0,len);
                    if (writernamesub != writername)
                    {
                        searchbooks.remove(i);
                        i--;
                    }
                }
                else{
                    searchbooks.remove(i);
                    i--;
                }
            }
        }
        if (ui->lineEdit_2->text() != "")
        {
            QString bookname = ui->lineEdit_2->text();

            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = bookname.length();
                if (len <= searchbooks[i].name.length())
                {
                    QString booknamesub = searchbooks[i].name.mid(0,len);
                    if (booknamesub != bookname)
                    {
                        searchbooks.remove(i);
                        i--;
                    }
                }
                else{
                    searchbooks.remove(i);
                    i--;
                }
            }
        }
        if (ui->lineEdit_3->text() != "")
        {
            QString publishername = ui->lineEdit_3->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = publishername.length();
                if (len <= searchbooks[i].publisher.length())
                {
                    QString publishernamesub = searchbooks[i].publisher.mid(0,len);
                    if (publishernamesub != publishername)
                    {
                        searchbooks.remove(i);
                        i--;
                    }

                }
                else{
                    searchbooks.remove(i);
                    i--;
                }
            }
        }
    }
   if (type == "Science")
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].kind == "Science")
            {
                searchbooks.push_back(books[i]);
            }
        }
        if (ui->lineEdit->text() != "")
        {
            QString writername = ui->lineEdit->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = writername.length();
                if (len <= searchbooks[i].writer.length())
                {
                    QString writernamesub = searchbooks[i].writer.mid(0,len);
                    if (writernamesub != writername)
                    {
                        searchbooks.remove(i);
                        i--;
                    }
                }
                else{
                    searchbooks.remove(i);
                    i--;
                }
            }
        }
        if (ui->lineEdit_2->text() != "")
        {
            QString bookname = ui->lineEdit_2->text();

            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = bookname.length();
                if (len <= searchbooks[i].name.length())
                {
                    QString booknamesub = searchbooks[i].name.mid(0,len);
                    if (booknamesub != bookname)
                    {
                        searchbooks.remove(i);
                        i--;
                    }
                }
                else{
                    searchbooks.remove(i);
                    i--;
                }
            }
        }
        if (ui->lineEdit_3->text() != "")
        {
            QString publishername = ui->lineEdit_3->text();
            for (int i = 0; i < searchbooks.size(); i++)
            {
                int len = publishername.length();
                if (len <= searchbooks[i].publisher.length())
                {
                    QString publishernamesub = searchbooks[i].publisher.mid(0,len);
                    if (publishernamesub != publishername)
                    {
                        searchbooks.remove(i);
                        i--;
                    }

                }
                else
                {
                    searchbooks.remove(i);
                    i--;
                }
            }
        }

    }
   ui->tableWidget->clearContents();
   ui->tableWidget->setRowCount(0);
   int count = 0;
   for (int i = 0; i < searchbooks.size(); i++)
   {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(count,0,new QTableWidgetItem(searchbooks[i].name));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem(searchbooks[i].writer));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(searchbooks[i].kind));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem(searchbooks[i].publisher));
        ui->tableWidget->setItem(count,4,new QTableWidgetItem(searchbooks[i].stock));
        count ++;
    }
}

