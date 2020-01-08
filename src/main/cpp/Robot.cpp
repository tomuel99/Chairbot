/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>
#include <iostream>
#include <memory>
#include <string>
//weeee github
//wii live in a society
#include <SageFunctions.h>
//#include <cameraServer/CameraServer.h>
#include <frc/IterativeRobot.h>
#include <frc/Joystick.h>
#include <frc/SmartDashboard/SendableChooser.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/Timer.h>
#include <frc/Talon.h>
//#include <frc/Encoder.h>
#include <frc/WPILib.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/LiveWindow/LiveWindow.h>
#include "networktables/NetworkTable.h"
#include "networkTables/NetworkTableInstance.h"
#include <ctre/Phoenix.h>
#include "rev/SparkMax.h"

//#include <math.h>

WPI_TalonSRX frontRight{12}, backRight{14}, backLeft{0};
frc::Joystick stick{0};
rev::SparkMax frontLeft{0};
frc::RobotDrive myRobot{frontLeft, frontRight, backLeft, backRight};
frc::Timer timer;
frc::SendableChooser autoChoice;

double speed, turn, sensitivity;
bool isUpPressed, isDownPressed;

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  frc::SmartDashboard::PutNumber("Timer", timer.Get());
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  timer.Reset();
  timer.Start();
  turn = 0;
  speed = 0;
  sensitivity = 0.5;
}

void Robot::TeleopPeriodic() {
  //increase sensitivity with the right bumper
  if (stick.GetRawButton(1) && sensitivity < 1.0) {
    sensitivity += 0.01;
  }
  else if (stick.GetRawButton(1)) {
    sensitivity += 0;
  }
  else if (stick.GetRawButton(2) && sensitivity > 0.0) {
    sensitivity -= 0.01;
  }
  else if (stick.GetRawButton(2)) {
    sensitivity -= 0;
  }
  else {
    sensitivity = sensitivity;
  }
  if (sensitivity >= 1.0) {
    sensitivity = 1.0;
  }
  else if (sensitivity <= 0) {
    sensitivity = 0.0;
  }
  else {}
  //drive with the left joystick
  turn = -stick.GetRawAxis(1) * 0.95;
  speed = stick.GetRawAxis(4) * sensitivity;
  myRobot.ArcadeDrive(speed, turn);
}

void Robot::TestPeriodic() {
  frc::SmartDashboard::PutString("Haha, you fool!", "Thundercross split attack!");
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
