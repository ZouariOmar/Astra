---------------------
-- Employees Table --
---------------------
CREATE TABLE Employees (
  EmployeeID NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
  Username VARCHAR2(100) GENERATED ALWAYS AS (LOWER(FirstName || LastName || EmployeeID)) UNIQUE NOT NULL,
  FirstName VARCHAR2(20) NOT NULL,
  LastName VARCHAR2(20) NOT NULL,
  Email VARCHAR2(255) UNIQUE NOT NULL,
  JobTitle VARCHAR2(20) DEFAULT NULL,
  Salary NUMBER(10, 2) DEFAULT NULL,
  HireDate DATE DEFAULT SYSDATE,
  Status VARCHAR2(10) DEFAULT 'Active' CHECK (UPPER(Status) IN ('ACTIVE', 'INACTIVE')),
  Password VARCHAR2(255) NOT NULL,
  ProfileImage VARCHAR2(255) DEFAULT NULL,
  PhoneNumber VARCHAR2(20) DEFAULT NULL,
  Address VARCHAR2(100) DEFAULT NULL,
  BirthDate DATE DEFAULT NULL,
  Department VARCHAR2(20) DEFAULT NULL,
  LastLogin TIMESTAMP DEFAULT NULL,
  LastPasswordReset TIMESTAMP DEFAULT NULL
);
/*
  Admin info           -  3 omarzouari3 Omar Zouari zouariomar20@gmail.com Admin  14-FEB-25 Active 1234
 Select Age            - TRUNC(MONTHS_BETWEEN(SYSDATE, BirthDate) / 12) AS Age
 Select YearsOfService - TRUNC(MONTHS_BETWEEN(SYSDATE, HireDate) / 12) AS YearsOfService
 */