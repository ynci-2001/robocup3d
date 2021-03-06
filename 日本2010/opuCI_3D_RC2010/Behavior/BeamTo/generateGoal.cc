#include "beamto.ih"

rf<Behavior::Goal> BeamTo::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  WorldModel& wm = WorldModel::getInstance();
  WorldModel::PlayMode pm = wm.getPlayMode();

// * unum 1 player(attacker)  * in right side
  if(wm.getSide() == WorldModel::RIGHT && wm.getUnum() == 3 )
  {
//       int j;
//        std::cout << "RIGHT and 1" << std::endl;
//        std::cin >> j;
      con->addVar("X", -3.0, -3.0);
      con->addVar("Y", d_y, d_y);
      con->addVar("Z", d_z, d_z);
  }
  else
  {
//       std::cout << "side:" << ((wm.getSide() == WorldModel::RIGHT) ? "RIGHT" : "LEFT")
//  << ", unum:" << wm.getUnum() << std::endl;
//        int i;
//        std::cin >> i;
      con->addVar("X", d_x, d_x);
      con->addVar("Y", d_y, d_y);
      con->addVar("Z", d_z, d_z);
  }
//  std::cout << "gGoal: (X, Y, Z) = (" << d_x << ", " << d_y << ", " << d_z << ")" << std::endl;
  
  return goal;
}
