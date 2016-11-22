/*
 Copyright (c) 2014, Robot Control and Pattern Recognition Group, Warsaw University of Technology
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the Warsaw University of Technology nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL <COPYright HOLDER> BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common_behavior/abstract_behavior.h"

#include "velma_low_level_interface_msgs/VelmaLowLevelCommand.h"
#include "velma_low_level_interface_msgs/VelmaRealEffectorStatus.h"

#include "common_predicates.h"

using namespace velma_low_level_interface_msgs;

class BehaviorIdle : public BehaviorBase<VelmaRealEffectorStatus, VelmaLowLevelCommand> {
public:
    typedef VelmaRealEffectorStatus TYPE_BUF_LO;
    typedef VelmaLowLevelCommand TYPE_BUF_HI;

    BehaviorIdle();

    virtual bool checkErrorCondition(
            const TYPE_BUF_LO& buf_lo, //const interface_ports::ContainerOuter &buf_lo_info,
            const TYPE_BUF_HI& buf_hi, //const interface_ports::ContainerOuter &buf_hi_info,
            const std::vector<RTT::TaskContext*> &components) const;

    virtual bool checkStopCondition(
            const TYPE_BUF_LO& buf_lo, //const interface_ports::ContainerOuter &buf_lo_info,
            const TYPE_BUF_HI& buf_hi, //const interface_ports::ContainerOuter &buf_hi_info,
            const std::vector<RTT::TaskContext*> &components) const;
};

BehaviorIdle::BehaviorIdle() :
    BehaviorBase("idle")
{
    addRunningComponent("bypass");
}

bool BehaviorIdle::checkErrorCondition(
            const TYPE_BUF_LO& buf_lo, //const interface_ports::ContainerOuter &buf_lo_info,
            const TYPE_BUF_HI& buf_hi, //const interface_ports::ContainerOuter &buf_hi_info,
            const std::vector<RTT::TaskContext*> &components) const
{
    bool rLwrOk = isLwrOk(buf_lo.rArmFriRobot, buf_lo.rArmFriIntf);
    bool lLwrOk = isLwrOk(buf_lo.lArmFriRobot, buf_lo.lArmFriIntf);
    bool rLwrCmd = isLwrInCmdState(buf_lo.rArmFriIntf);
    bool lLwrCmd = isLwrInCmdState(buf_lo.lArmFriIntf);
    bool hwOk = (rLwrOk && lLwrOk && rLwrCmd && lLwrCmd);

    if (hwOk && isCmdValid(buf_hi) && isStatusValid(buf_lo))
    {
        return false;
    }

    return true;
}

bool BehaviorIdle::checkStopCondition(
            const TYPE_BUF_LO& buf_lo, //const interface_ports::ContainerOuter &buf_lo_info,
            const TYPE_BUF_HI& buf_hi, //const interface_ports::ContainerOuter &buf_hi_info,
            const std::vector<RTT::TaskContext*> &components) const
{
    return false;
}

static BehaviorRegistrar<VelmaRealEffectorStatus, VelmaLowLevelCommand, BehaviorIdle> registrar("idle");
