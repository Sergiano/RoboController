using System;
using System.Windows.Forms;
using RoboController;

namespace DemoController
{
    public partial class Form1 : Form
    {
        private Connector _connector;
        private TankController _tankController;

        public Form1()
        {
            InitializeComponent();
        }

        private void _buttonConnect_Click(object sender, EventArgs e)
        {
            _tankController = new TankController(_textBoxComPort.Text);
            if (_tankController.IsConnected)
            {
                _buttonConnect.Text = "Подключено";
                _textBoxComPort.Visible = false;
            }
        }

        private void _buttonUp_Click(object sender, EventArgs e)
        {
            _tankController.SetCommand(TankCommand.COMMAND_UP);
        }

        private void _buttonDown_Click(object sender, EventArgs e)
        {
            _tankController.SetCommand(TankCommand.COMMAND_DOWN);
        }

        private void _buttonLeft_Click(object sender, EventArgs e)
        {
            _tankController.SetCommand(TankCommand.COMMAND_LEFT);
        }

        private void _buttonRight_Click(object sender, EventArgs e)
        {
            _tankController.SetCommand(TankCommand.COMMAND_RIGTH);
        }
    }
}
