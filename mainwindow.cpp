#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

Node::Node(int id, int pId, std::string caption, bool status, std::string Message)
{
	this->id = id;
	this->pId = pId;
	this->caption = caption;
	this->status = status;
	this->Message = Message;

}
Node::Node(){}

void Node::setId(int id) {
	this->id = id;
}
void Node::setpId(int pId) {
	this->pId = pId;
}
void Node::setCaption(std::string caption) {
	this->caption = caption;
}
void Node::setStatus(bool status) {
	this->status = status;
}
void Node::setMessage(std::string message) {
	this->Message = message;
}

int Node::getId() {
	return this->id;
}
int Node::getpId() {
	return this->pId;
}
std::string Node::getCaption() {
	return  this->caption;
}
bool Node::getStatus() {
	return this->status;
}
std::string Node::getMessage() {
	return this->Message;
}

QVector<std::shared_ptr<Node>> parseTxtToVec(std::string path) {
	QVector<std::shared_ptr<Node>> nodeList;
	std::ifstream infile(path);
	while (!infile.eof()) {
		std::string str;
		auto node = std::make_shared<Node>();
		std::getline(infile, str, ':');
		node->setId(std::stoi(str));
		std::getline(infile, str, ':');
		node->setpId(std::stoi(str));
		std::getline(infile, str, ':');
		node->setCaption(str);
		std::getline(infile, str, ':');
		node->setStatus(str == "0" ? false : true);
		std::getline(infile, str);
		node->setMessage(str);

		nodeList.emplace_back(node);
	}
	return nodeList;

}

int countChild(QVector<std::shared_ptr<Node>> NodeList, int id){
  int count = 0;
  for(auto node : NodeList){
      if(node->getpId() == id){
          count++;
        }
    }
  return count;
}
void appendChilds(QVector<std::shared_ptr<Node>> NodeList, QStandardItem* item, std::shared_ptr<Node> node){
  for(auto node2 : NodeList){
      if(node2->getpId() == node->getId()){
          QStandardItem* item2 = new QStandardItem(QString::fromStdString(node2->getCaption()));
          item->appendRow(item2);
          if(countChild(NodeList, node2->getId())>0){
              appendChilds(NodeList, item2, node2);
            }
        }
    }
}
//void insertModel(QTreeView tree, )
void MainWindow::on_pushButton_clicked(){
  NodeList = parseTxtToVec(QFileDialog::getOpenFileName(nullptr, "", "D:\\", "*.txt").toStdString());
  QStandardItemModel* model = new QStandardItemModel(nullptr);
  QStandardItem* root = model->invisibleRootItem();

  for(auto node : NodeList){
      if(node->getpId()==-1){
          QStandardItem* item = new QStandardItem(QString::fromStdString(node->getCaption()));
          root->appendRow(item);
          if(countChild(NodeList, node->getId())>0){
              appendChilds(NodeList, item, node);
            }
        }
    }
  ui->treeView->setModel(model);
}


void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{

}

