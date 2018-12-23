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
        private Thread readThread;
        public const int portBaudRate = 9600;
        public Queue<string> messages = new Queue<string>();

        private void initianalPort()
        {
            _serialPort = new SerialPort();
            _continue = false;
        }

        public void ConnectToPort(string portName)
        {
            initianalPort();
            TryClosePort();
            readThread = new Thread(Read);
            _serialPort.PortName = SetPortName(portName);
            _serialPort.BaudRate = portBaudRate;
            _serialPort.ReadTimeout = 500;
            _serialPort.WriteTimeout = 500;

            _serialPort.Open();
            _continue = true;
            readThread.Start();
        }

        public void TryClosePort()
        {
            if (_continue)
            {
                readThread.Join();
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
                    messages.Enqueue(message);
                }
                catch (TimeoutException) { }
            }
        }

        public string GetMessage()
        {
            if (messages.Count > 0)
            {
                return messages.Dequeue();
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
