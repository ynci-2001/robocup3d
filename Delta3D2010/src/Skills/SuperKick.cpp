/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "SuperKick.h"
#include "../WorldModel/WorldModel.h" 
#include "../Effectors/AngularMotor.h"
#include "../Behavior/BhvBasicKick.h"

bool SuperKick::mPrepare;
bool SuperKick::mPrepareDone;
bool SuperKick::mKickDone ;

SuperKick::SuperKick()
{
  S << "10 20 33 40 45 0 0 0 350 0 0 -0 0 0 0 0 0 0 -1 -0 1 0 0 0 0 0 -1 0 0 0 0 0 0 0 0 2 -3  3 6 -0 -0 0  0 0 0 -0 -6 0 0 0 0 -4.3 -3 1 6 0 0 0 0 0 0 -0 -6 0 0 0 0 2.5 2.9 -3.3 -3 -0 0 0 0 0 0 0 6 0 0 0 1.2 0 0 0 0 0 0 0 1.2 0 0 0 0 0 0 0 ";
   mPrepare=false;
   mPrepareDone=false;
   mKickDone = false;
   WM = boost::shared_ptr<WorldModel>(& WorldModel::instance());
}

SuperKick& SuperKick::instance()
{
    static SuperKick sSuperKick;
    return sSuperKick;
}

void SuperKick::execute(bool isLeftHold)
{
   std::string cmd;
   Effectors::instance().mActionCommand="";
   if( !mPrepareDone )  
   {
         prepare();
//          cout<<"if alakiiiiiiiiiiiiiiiiiiiiiiiiii";
         Connection::instance().sendMessage(Effectors::instance().mActionCommand);     
    }
    else
    {
//       cout<<"else is Executingggggggggggggggggggg";
      Kicking(cmd,isLeftHold);
      Connection::instance().sendMessage(Effectors::instance().mActionCommand);
    }
 }

///this method prepare the agent for Kicking
bool SuperKick::prepare()
{        
   WorldModel& wm = WorldModel::instance();
   Walk& walk = Walk::instance();


   Effectors::instance().calculateVel(JID_LARM_1, -45, 3);
   Effectors::instance().calculateVel(JID_RARM_1, -45, 3);

   Effectors::instance().calculateVel(JID_LLEG_4, 0, 3.5);
   Effectors::instance().calculateVel(JID_RLEG_4, 0, 3.5);

   Effectors::instance().calculateVel(JID_LLEG_3, 0, 3);
   Effectors::instance().calculateVel(JID_RLEG_3, 0, 3);

   Effectors::instance().calculateVel(JID_LLEG_5, 0, 2);
   Effectors::instance().calculateVel(JID_RLEG_5, 0, 2);

   Effectors::instance().setActionCommand();
   
   if(//WorldModel::instance().getHJoint(JID_LARM_1).angle<-43 &&
      //WorldModel::instance().getHJoint(JID_RARM_1).angle<-43 &&
       //WorldModel::instance().getHJoint(JID_LLEG_4).angle<2  &&
       //WorldModel::instance().getHJoint(JID_RLEG_4).angle<2  &&
       //WorldModel::instance().getHJoint(JID_LLEG_3).angle<2  &&
       //WorldModel::instance().getHJoint(JID_RLEG_3).angle<2  &&
       WorldModel::instance().getHJoint(JID_LLEG_5).angle<2  &&
       WorldModel::instance().getHJoint(JID_RLEG_5).angle<2 
      )
         
   { 
      mPrepare=true;
      mPrepareDone=true;
      return true;
      
   }
   return false;
}

int SuperKick::Kicking(std::string &cmd,bool isLeftHold)
{
    Effectors& eff= Effectors::instance();
    static int cycle = 2, t = 0;
    int endCycle = 150;
    
    static shootJoint Shoot;
    stringstream ss;
     if (cycle==2 || t==0)
     {  
       mKickDone=false;
        eff.mActionCommand="";
     }
       ///if kicking was finished all joint will stop by fix method  
    if (mKickDone)
    {
        cmd=fix();
	eff.mActionCommand="";
        eff.mActionCommand = cmd;
        return 0;
    }
    ///if this method was called for the first time then shoot value will read from file
    if (cycle == 2)
        importShootJoint(Shoot,isLeftHold);
    if (cycle < Shoot.time[t]) 
    {
             ss << fix()
                << "(lae1" << Shoot.lae1[t] << ")"
                << "(rae1 " << Shoot.rae1[t] << ")"
                << "(lae2 " << Shoot.lae2[t] << ")"
                << "(rae2 " << Shoot.rae2[t] << ")"
                << "(lle1 " << Shoot.lle1[t] << ")"
                << "(rle1 " << Shoot.rle1[t] << ")"
                << "(lle2 " << Shoot.lle2[t] << ")"
                << "(rle2 " << Shoot.rle2[t] << ")"
                << "(lle3 " << Shoot.lle3[t] << ")"
                << "(rle3 " << Shoot.rle3[t] << ")"
                << "(lle4 " << Shoot.lle4[t] << ")"
                << "(rle4 " << Shoot.rle4[t] << ")"
                << "(lle5 " << Shoot.lle5[t] << ")"
                << "(rle5 " << Shoot.rle5[t] << ")"
                << "(lle6 " << Shoot.lle6[t] << ")"
                << "(rle6 " << Shoot.rle6[t] << ")";
        cmd = ss.str();
        eff.mActionCommand="";
	eff.mActionCommand=cmd;
    }
    if (cycle > Shoot.time[t])
    {
        
        cmd = resetJointShoot(endCycle - cycle);
        eff.mActionCommand="";
	eff.mActionCommand=cmd;
    }
    cycle++;
    if (cycle == Shoot.time[t])
        t++;

    if (endCycle == cycle) 
    {
        cycle = 2;
	t = 0;
	mKickDone = true;
	//mPrepare=false;
// 	WorldModel::instance().setCurrentAction(ACT_WALK);
        mPrepareDone=false;
        mPrepare=false;
        cmd = fix();
        eff.mActionCommand="";
        eff.mActionCommand=cmd; 
    }
    return (endCycle - cycle);
}

/////////////////////////////////////////////////////////////////////////

void SuperKick::importShootJoint(shootJoint& Shoot,bool leftFoot) 
{
    string str;
///full shoot joints by file value
    for (int i = 0; i < 10; i++)
        S >> Shoot.time[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle1[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle2[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.lle2[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle3[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.lle3[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle4[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.lle4[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle5[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.lle5[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.rle6[i];
    for (int i = 0; i < 8; i++)
        S >> Shoot.lle6[i];
    
    for (int i = 0; i < 8; i++) 
    {
        Shoot.lle1[i] = 0;
        Shoot.lae1[i] = 0;
        Shoot.rae1[i] = 0;
        Shoot.lae2[i] = 0;
        Shoot.rae2[i] = 0;
    }
    Shoot.lae2[0] = 2;
    Shoot.lae2[1] = 2;
    Shoot.lae2[2] = 1.5;
    
    ///shoooting by left foot
    if (leftFoot) 
    { 
        for (int i = 0; i < 8; i++) 
	{
            Shoot.rle2[i] *= -1;
            Shoot.lle2[i] *= -1;
            Shoot.rle6[i] *= -1;
            Shoot.lle6[i] *= -1;

            double t = Shoot.rle3[i];
            Shoot.rle3[i] = Shoot.lle3[i];
            Shoot.lle3[i] = t;
            t = Shoot.rle4[i];
            Shoot.rle4[i] = Shoot.lle4[i];
            Shoot.lle4[i] = t;
            t = Shoot.rle5[i];
            Shoot.rle5[i] = Shoot.lle5[i];
            Shoot.lle5[i] = t;
            t = Shoot.rae2[i];
            Shoot.rae2[i] = -1 * Shoot.lae2[i];
            Shoot.lae2[i] = t;
            t = Shoot.rle2[i];
            Shoot.rle2[i] = Shoot.lle2[i];
            Shoot.lle2[i] = t;
            t = Shoot.rle6[i];
            Shoot.rle6[i] = Shoot.lle6[i];
            Shoot.lle6[i] = t;

        }


    }
}

string SuperKick::fix() 
{
   stringstream ss;

   for (int i = (int)JID_HEAD_1; i <= (int)JID_RLEG_6; i++) 
      ss << moveJoint(WM->mJointEffectorMap[static_cast<EJointID>(i)],0);

   return ss.str();
}



string SuperKick::resetJointShoot(int nextcycle) {
    stringstream ss;
    ss << fix();
    for (int i = (int)JID_HEAD_1; i <= (int)JID_RLEG_6; i++) {
        if (i == 10 || i == 11)
            ss << moveJoint(WM->mJointEffectorMap[static_cast<EJointID>(i)], -2 * WM->getHJoint(static_cast<EJointID>(i)).angle / nextcycle);
        else
            ss << moveJoint(WM->mJointEffectorMap[static_cast<EJointID>(i)], -1 * WM->getHJoint(static_cast<EJointID>(i)).angle / nextcycle);
    }
    return ss.str();
}




string SuperKick::moveJoint(string j, double val) {
    stringstream message;
    message << "(" << j << " " << val << ")";
    return message.str();
}

/*

mSlowGain = 0.01f;

salt::Vector3f torsoPos(-0.055, 0.0, 0.3201),
                   holdPos(-0.045, 0.0, 0.015),
                   movePos(0.045, -0.04, 0.05);

salt::Vector3f torsoPos(-0.035, -0.02, 0.3801),
                   holdPos(-0.045, 0.0, 0.015),
                   movePos(0.045, 0.1, 0.05);


prepare:
salt::Vector3f torsoPos(-0.055, 0.0, 0.3199),
                   holdPos(-0.06, 0.0, 0.015),
                   movePos(0.045, -0.05, 0.05);
shoot:
salt::Vector3f torsoPos(-0.035, -0.032, 0.3801),
                   holdPos(-0.045, 0.0, 0.015),
                   movePos(0.065, 0.02, 0.05);


back prepare
  salt::Vector3f torsoPos(-0.055, 0.0, 0.3199),
                   holdPos(-0.06, 0.0, 0.015),
                   movePos(0.045, 0.02, 0.02);

back shoot
t::Vector3f torsoPos(-0.035, -0.032, 0.3801),
                   holdPos(-0.045, 0.0, 0.015),
                   movePos(0.045, -0.15, 0.07);




                    uLINK[JID_LLEG_5].p

*/