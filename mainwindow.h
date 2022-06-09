#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QObject>
#include <string>
#include <iterator>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Node {
private:
	int id;
	int pId;
	std::string caption;
	bool status;
	std::string Message;

public:

	Node(int id, int pId, std::string caption, bool status, std::string Message);
	Node();
	void setId(int id);
	void setpId(int pId);
	void setCaption(std::string caption);
	void setStatus(bool status);
	void setMessage(std::string);

	int getId();
	int getpId();
	std::string getCaption();
	bool getStatus();
	std::string getMessage();
};
void appendChilds(QVector<std::shared_ptr<Node>> NodeList, QStandardItem* item, std::shared_ptr<Node> node);
QVector<std::shared_ptr<Node>> parseTxtToVec(std::string);
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_treeView_doubleClicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  QFile file;
  QVector<std::shared_ptr<Node>> NodeList;
};
#endif // MAINWINDOW_H
