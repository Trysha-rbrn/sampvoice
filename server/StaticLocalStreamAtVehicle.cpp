/*
    This is a SampVoice project file
    Developer: CyberMor <cyber.mor.2020@gmail.ru>

    See more here https://github.com/CyberMor/sampvoice

    Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#include "StaticLocalStreamAtVehicle.h"

#include <cstring>

#include "ControlPacket.h"
#include "Header.h"

StaticLocalStreamAtVehicle::StaticLocalStreamAtVehicle(
    const float distance, const uint16_t vehicleId,
    const uint32_t color, const std::vector<char>& name
)
    : LocalStream(distance)
{
    const auto nameString = name.data();
    const auto nameLength = name.size();

    PackWrap(this->packetCreateStream, SV::ControlPacketType::createLStreamAtVehicle, sizeof(SV::CreateLStreamAtPacket) + nameLength);

    PackGetStruct(&*this->packetCreateStream, SV::CreateLStreamAtPacket)->stream = reinterpret_cast<uint32_t>(static_cast<Stream*>(this));
    std::memcpy(PackGetStruct(&*this->packetCreateStream, SV::CreateLStreamAtPacket)->name, nameString, nameLength);
    PackGetStruct(&*this->packetCreateStream, SV::CreateLStreamAtPacket)->distance = distance;
    PackGetStruct(&*this->packetCreateStream, SV::CreateLStreamAtPacket)->target = vehicleId;
    PackGetStruct(&*this->packetCreateStream, SV::CreateLStreamAtPacket)->color = color;
}
