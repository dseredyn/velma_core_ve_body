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

#ifndef DIAGNOSTIC_COMPONENT_H_
#define DIAGNOSTIC_COMPONENT_H_

#include <cstring>

#include <vector>
#include <string>

#include "rtt/RTT.hpp"
#include "rtt/os/TimeService.hpp"

#include <diagnostic_msgs/DiagnosticArray.h>

#include "velma_low_level_interface_msgs/VelmaLowLevelStatus.h"

using namespace velma_low_level_interface_msgs;

class DiagnosticComponent: public RTT::TaskContext {
public:
    explicit DiagnosticComponent(const std::string &name);

    bool configureHook();

    bool startHook();

    void stopHook();

    void updateHook();

private:

    class Diag {
    public:
        std::string component_name_;
        RTT::OperationCaller<std::string()> getDiag_;
    };

    diagnostic_msgs::DiagnosticArray diag_out_;
    RTT::OutputPort<diagnostic_msgs::DiagnosticArray > port_diag_out_;

    VelmaLowLevelStatusSC status_sc_in_;
    RTT::InputPort<VelmaLowLevelStatusSC> port_status_sc_in_;

    std::vector<TaskContext* > peers_;
    std::vector<Diag > diag_vec_;
};

#endif  // DIAGNOSTIC_COMPONENT_H_
