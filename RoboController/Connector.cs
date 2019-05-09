using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Threading;

namespace RoboController
{
    public class Connector
    {
        private SerialPort _serialPort;
        private bool _continue = false;
        private Thread _readThread;
        public const int PortBaudRate = 9600;
        public Queue<string> Messages = new Queue<string>();

        public bool IsConnected
        {
            get
            {
                return _continue;
            }
        }

        private void InitianalPort()
        {
            _serialPort = new SerialPort();
            _continue = false;
        }

        public void ConnectToPort(string portName)
        {
            InitianalPort();
            TryClosePort();
            _readThread = new Thread(Read);
            _serialPort.PortName = SetPortName(portName);
            _serialPort.BaudRate = PortBaudRate;
            _serialPort.ReadTimeout = 500;
            _serialPort.WriteTimeout = 500;

            _serialPort.Open();
            _continue = true;
            _readThread.Start();
        }

        public void TryClosePort()
        {
            if (_continue)
            {
                _readThread.Join();
                _serialPort.Close();
                _continue = false;
            }
        }

        public string SetPortName(string portName)
        {
            if (portName == "" || !(portName.ToLower()).StartsWith("com"))
            {
                portName = _serialPort.PortName;
            }
            return portName;
        }

        public void Read()
        {
            while (_continue)
            {
                try
                {
                    string message = _serialPort.ReadLine();
                    Messages.Enqueue(message);
                }
                catch (TimeoutException) { }
            }
        }

        public string GetMessage()
        {
            if (Messages.Count > 0)
            {
                return Messages.Dequeue();
            }
            else
            {
                return null;
            }
        }

        public void Write(char message)
        {
            _serialPort.Write(String.Format("{0}", message));
        }
    }
}
