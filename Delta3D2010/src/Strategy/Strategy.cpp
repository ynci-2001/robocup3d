//
// C++ Implementation: Strategy
//
// Description: 
//
//
// Author: delta3d team 2009 <deltateams2009@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "Strategy.h"
#include "../Agent_Roles/RoleGoalie.h"
#include "../Agent_Roles/RoleCenterMidFielder.h"
#include "../Agent_Roles/RoleLeftDefensive.h"
#include "../Agent_Roles/RoleRightDefensive.h"
#include "../Agent_Roles/RoleRightForward.h"
#include "../Agent/Agent.h"

Strategy::Strategy()
{
   m_homePosTeloranse= Vector3f(0.1,0.1,10);
   m_rangeTeloranse  = Vector2f(0.05,0.05); 
}

Strategy& Strategy::instance()
{
    static Strategy sStrategy;
    return sStrategy;
}

void Strategy::createRole()
{
//      Formation& formation = Formation::instance();
//        if(!Strategy::role)
//       {
//          TPlayerTypeMap::const_iterator  iter = 
//                          formation.mPlayerTypeMap.find(WorldModel::i().getUnum());
//          if(iter == formation.mPlayerTypeMap.end())
//          {
//            std::cout <<"error not find player"<<WorldModel::i().getUnum()
//                      <<"  in formation"<<std::endl;
// //           return false;
//          }
//          if( (* iter).second == PT_GOALKEEPER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleGoalie::create());
//            std::cout<< "RoleGoalie set"<<std::endl;
//          }
//          else if ((* iter).second == PT_CENTER_MIDFIELDER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleCenterMidFielder::create());
//            std::cout<< "RoleDefensive set"<<std::endl;
//          }
// 	 else if ((* iter).second == PT_LEFT_DEFENDER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleLeftDefensive::create());
//            std::cout<< "RoleDefensive set"<<std::endl;
//          }
// 	 else if ((* iter).second == PT_RIGHT_DEFENDER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleRightDefensive::create());
//            std::cout<< "RoleDefensive set"<<std::endl;
//          }
// 	 else if ((* iter).second == PT_LEFT_ATTACKER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleLeftForward::create());
//            std::cout<< "RoleDefensive set"<<std::endl;
//          }
//          else if((* iter).second == PT_RIGHT_ATTACKER )
//          {
//            Strategy::role = boost::shared_ptr<SoccerRole>(RoleRightForward::create());
//            std::cout<< "RoleForward set"<<std::endl;
//          }
//          else
//          {
//            std::cout<< "Error role not set"<<std::endl;
//          }
//      }
//     TeamPlayer::instance().think();

}

void Strategy::executeRole()
{
    if(Agent::role)
    {
       Agent::role->execute();
    }

}

PlayerType Strategy::getPlayerType(  ) const
{
    
    return Formation::instance().mPlayerTypeMap[WorldModel::instance().getUnum() ];
}

PlayerType Strategy::getPlayerType( const int number ) const
{
    if (  number < 1 || 11 <  number )
    {
        std::cout << ": Illegal number : " << number
                  << std::endl;
        return PT_NONE;
    }
    stringstream ss;
    ss<<number;
    return Formation::instance().mPlayerTypeMap[ ss.str() ];
}



void Strategy::analyzeOpponentFormation(  )
{




}


void Strategy::analyzeOpponentStrategy(  )
{




}

bool Strategy::gotoStrategyPos()
{
  
    WorldModel& wm = WorldModel::instance();
    Formation& formation = Formation::instance();
    std::string num= wm.getUnum();
  
    TPlayerTypeMap::iterator iter =
                         formation.mPlayerTypeMap.find(num);
    if(iter == formation.mPlayerTypeMap.end())
    {
       std::cout<<"Error: player not found in formation"<<std::cout;
       return false;
    }
    //std::cout<<"in goto strategi "<<Strategy::instance().gotoStrategyPos()<<std::endl;
    return BhvBasicWalk(Vector2f(formation.mFormationDataMap[(*iter).second].homePos.x(),formation.mFormationDataMap[(*iter).second].homePos.y() )).execute();
    
}

bool Strategy::gotoHomePos()
{
  
    WorldModel& wm = WorldModel::instance();
    Formation& formation = Formation::instance();
    std::string num= wm.getUnum();
  
    TPlayerTypeMap::iterator iter =
                         formation.mPlayerTypeMap.find(num);
    if(iter == formation.mPlayerTypeMap.end())
    {
       std::cout<<"Error: player not found in formation"<<std::cout;
       return false;
    }
    BhvBasicWalk(  Vector2f(formation.mFormationDataMap[(*iter).second].homePos.x(),formation.mFormationDataMap[(*iter).second].homePos.y() )  );
    return true;
    
}

bool Strategy::isInHomePos()
{
  
    WorldModel& wm = WorldModel::instance();
    Formation& formation = Formation::instance();
    std::string num= wm.getUnum();
    Vector3f myPos=WorldModel::instance().getMyPos();
    
    TPlayerTypeMap::iterator iter =
                         formation.mPlayerTypeMap.find(num);
    if(iter == formation.mPlayerTypeMap.end())
    {
       std::cout<<"Error: player not found in formation"<<std::cout;
       //return;
    }
  
    if( ( myPos.x() <  formation.mFormationDataMap[(*iter).second].homePos.x() + m_homePosTeloranse.x() ) &&
        ( myPos.x() >  formation.mFormationDataMap[(*iter).second].homePos.x() - m_homePosTeloranse.x() ) &&
	( myPos.y() <  formation.mFormationDataMap[(*iter).second].homePos.y() + m_homePosTeloranse.y() ) &&
        ( myPos.y() >  formation.mFormationDataMap[(*iter).second].homePos.y() - m_homePosTeloranse.y() ) //&&
	//( myPos.z() <  formation.mFormationDataMap[(*iter).second].homePos.z() + m_homePosTeloranse.z() ) &&
	//( myPos.z() >  formation.mFormationDataMap[(*iter).second].homePos.z() - m_homePosTeloranse.z() ) 
      )
       return true;
       
    return false;
	 
}

bool Strategy::isInRange()
{
   WorldModel& wm = WorldModel::instance();
   Formation& formation = Formation::instance();
   std::string num= wm.getUnum();
   Vector3f ballPos = WorldModel::instance().getBallPos();
    TPlayerTypeMap::iterator iter =
                         formation.mPlayerTypeMap.find(num);
    if(iter == formation.mPlayerTypeMap.end())
    {
       std::cout<<"Error: player not found in formation"<<std::cout;
       //return;
    }
   
   if( ( ballPos.x() > formation.mFormationDataMap[(*iter).second].xRange.x() - m_rangeTeloranse.x() ) &&
       ( ballPos.x() < formation.mFormationDataMap[(*iter).second].xRange.y() + m_rangeTeloranse.x() ) &&
       ( ballPos.y() > formation.mFormationDataMap[(*iter).second].yRange.x() - m_rangeTeloranse.y() ) &&
       ( ballPos.y() < formation.mFormationDataMap[(*iter).second].yRange.y() + m_rangeTeloranse.y() )
     )
    
     return true;
   
   return false;

}
 
 bool Strategy::isInOppPenaltyArea(const Vector3f & pos)const
 {
  Vector3f topLeft(7.0,1.5,0) ,downRight(9,-1.5,0);
  
//   std::cout<<"pos is : "<<pos <<" & topLeft :"<<topLeft<<" downRight "<<downRight<<std::endl;
  return (pos.x() >= topLeft.x() && pos.y() <= topLeft.y() && pos.x()<= downRight.x() && pos.y() >= downRight.y());
 }

