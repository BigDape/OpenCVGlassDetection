#ifndef SIGNALCONTROLDATA_H
#define SIGNALCONTROLDATA_H

#include "RegParasComm.h"
#include "HSSocketInterface.h"

class SignalControlData : public SocketNameSpace::HSSocketInterface
{
public:
    SignalControlData(){}
    virtual ~SignalControlData(){}
    virtual void InitRegs(QString ip, int port) override;
    virtual void Trigger() override;
    virtual void SetAllRegs(SignalControl data) override;
    virtual void SetReg(unsigned short addr_s,
                        unsigned short addr_e,
                        unsigned int data) override;
    virtual void GetRealTimeData(unsigned int& FrameSignal, unsigned int& AlmLightSignal) override;
    virtual void GetAllData(SignalControl& data) override;
    virtual bool TestIPConnect() override;
private:
    RegParasComm m_pSig_comm;
};



#endif  // SIGNALCONTROLDATA_H
