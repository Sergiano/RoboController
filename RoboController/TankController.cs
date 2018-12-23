using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RoboController
{
    public enum TankCommand
    {
        NO_COMMAND,
        COMMAND_UP,
        COMMAND_DOWN,
        COMMAND_LEFT,
        COMMAND_RIGTH,
        COMMAND_TURRET_LEFT,
        COMMAND_TURRET_RIGHT,
        COMMAND_MOVE_GUN
    }
    public class TankController
    {
        private Connector _connector= new Connector();
        private TankCommand _currentCommand = TankCommand.NO_COMMAND;
        public TankController(string portName)
        {
            _connector.ConnectToPort(portName);
        }

        public void SetCommand(TankCommand tankCommand)
        {
            if (tankCommand != _currentCommand)
            {
                _currentCommand = tankCommand;

                sendCommand(_currentCommand);
            }
        }

        private void sendCommand(TankCommand tankCommand)
        {
            switch (tankCommand)
            {
                case TankCommand.COMMAND_UP:
                    {
                        _connector.Write('w');
                        break;
                    }
                case TankCommand.COMMAND_LEFT:
                    {
                        _connector.Write('a');
                        break;
                    }
                case TankCommand.COMMAND_DOWN:
                    {
                        _connector.Write('s');
                        break;
                    }
                case TankCommand.COMMAND_RIGTH:
                    {
                        _connector.Write('d');
                        break;
                    }
                case TankCommand.COMMAND_TURRET_LEFT:
                    {
                        _connector.Write('q');
                        break;
                    }
                case TankCommand.COMMAND_TURRET_RIGHT:
                    {
                        _connector.Write('e');
                        break;
                    }
                case TankCommand.COMMAND_MOVE_GUN:
                    {
                        _connector.Write('c');
                        break;
                    }
                case TankCommand.NO_COMMAND:
                    {
                        _connector.Write('r');
                        break;
                    }
                default:
                    {
                        _connector.Write('r');
                        break;
                    }
            }
        }
    }
}
