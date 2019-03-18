namespace DemoController
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this._textBoxComPort = new System.Windows.Forms.TextBox();
            this._buttonConnect = new System.Windows.Forms.Button();
            this._buttonUp = new System.Windows.Forms.Button();
            this._buttonDown = new System.Windows.Forms.Button();
            this._buttonLeft = new System.Windows.Forms.Button();
            this._buttonRight = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _textBoxComPort
            // 
            this._textBoxComPort.Location = new System.Drawing.Point(12, 12);
            this._textBoxComPort.Name = "_textBoxComPort";
            this._textBoxComPort.Size = new System.Drawing.Size(100, 20);
            this._textBoxComPort.TabIndex = 0;
            // 
            // _buttonConnect
            // 
            this._buttonConnect.Location = new System.Drawing.Point(118, 9);
            this._buttonConnect.Name = "_buttonConnect";
            this._buttonConnect.Size = new System.Drawing.Size(100, 23);
            this._buttonConnect.TabIndex = 1;
            this._buttonConnect.Text = "Подключиться";
            this._buttonConnect.UseVisualStyleBackColor = true;
            this._buttonConnect.Click += new System.EventHandler(this._buttonConnect_Click);
            // 
            // _buttonUp
            // 
            this._buttonUp.Location = new System.Drawing.Point(93, 38);
            this._buttonUp.Name = "_buttonUp";
            this._buttonUp.Size = new System.Drawing.Size(75, 23);
            this._buttonUp.TabIndex = 2;
            this._buttonUp.Text = "Up";
            this._buttonUp.UseVisualStyleBackColor = true;
            this._buttonUp.Click += new System.EventHandler(this._buttonUp_Click);
            // 
            // _buttonDown
            // 
            this._buttonDown.Location = new System.Drawing.Point(93, 81);
            this._buttonDown.Name = "_buttonDown";
            this._buttonDown.Size = new System.Drawing.Size(75, 23);
            this._buttonDown.TabIndex = 3;
            this._buttonDown.Text = "Down";
            this._buttonDown.UseVisualStyleBackColor = true;
            this._buttonDown.Click += new System.EventHandler(this._buttonDown_Click);
            // 
            // _buttonLeft
            // 
            this._buttonLeft.Location = new System.Drawing.Point(12, 58);
            this._buttonLeft.Name = "_buttonLeft";
            this._buttonLeft.Size = new System.Drawing.Size(75, 23);
            this._buttonLeft.TabIndex = 4;
            this._buttonLeft.Text = "Left";
            this._buttonLeft.UseVisualStyleBackColor = true;
            this._buttonLeft.Click += new System.EventHandler(this._buttonLeft_Click);
            // 
            // _buttonRight
            // 
            this._buttonRight.Location = new System.Drawing.Point(174, 58);
            this._buttonRight.Name = "_buttonRight";
            this._buttonRight.Size = new System.Drawing.Size(75, 23);
            this._buttonRight.TabIndex = 5;
            this._buttonRight.Text = "Right";
            this._buttonRight.UseVisualStyleBackColor = true;
            this._buttonRight.Click += new System.EventHandler(this._buttonRight_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(260, 118);
            this.Controls.Add(this._buttonRight);
            this.Controls.Add(this._buttonLeft);
            this.Controls.Add(this._buttonDown);
            this.Controls.Add(this._buttonUp);
            this.Controls.Add(this._buttonConnect);
            this.Controls.Add(this._textBoxComPort);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox _textBoxComPort;
        private System.Windows.Forms.Button _buttonConnect;
        private System.Windows.Forms.Button _buttonUp;
        private System.Windows.Forms.Button _buttonDown;
        private System.Windows.Forms.Button _buttonLeft;
        private System.Windows.Forms.Button _buttonRight;
    }
}

