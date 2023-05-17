#include "form.h"

#include "ui_form.h"

Form::Form(QWidget* parent) noexcept : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  connect(ui->pushButton_ok, SIGNAL(clicked()), this,
          SLOT(OnPushButtonOkClicked()));
}

Form::~Form() { delete ui; }

QString Form::GetInputX() noexcept { return OnPushButtonOkClicked(); }

QString Form::OnPushButtonOkClicked() noexcept {
  QString x_value = ui->lineEdit_input->text();
  this->close();
  emit mainWindow();
  return x_value;
}

void Form::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Return) {
    this->close();
    emit mainWindow();
  }
}
