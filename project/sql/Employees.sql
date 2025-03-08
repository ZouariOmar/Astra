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
  Status VARCHAR2(10) DEFAULT 'Active' CHECK (
    UPPER(Status) IN ('ACTIVE', 'INACTIVE', 'SUSPENDED')
  ),
  Password VARCHAR2(255) NOT NULL,
  ProfileImage VARCHAR2(255) DEFAULT NULL,
  PhoneNumber VARCHAR2(20) DEFAULT NULL,
  Address VARCHAR2(100) DEFAULT NULL,
  BirthDate DATE DEFAULT NULL,
  Department VARCHAR2(20) DEFAULT NULL,
  LastLogin TIMESTAMP DEFAULT NULL,
  LastPasswordReset TIMESTAMP DEFAULT NULL
);

CREATE TABLE personnel(t INT);
CREATE TABLE Boutique(t INT);
CREATE TABLE Commercant(t INT);
CREATE TABLE partenaire(t INT);
CREATE TABLE événements(t INT);
/*
 List all Astra tables - SELECT table_name FROM user_tables;
 Admin info            - INSERT INTO Employees (FirstName, LastName, Email, JobTitle, Status, Password) VALUES ('Omar', 'Zouari', 'zouariomar20@gmail.com', 'Admin', 'ACTIVE', '1234')
 Select Age            - TRUNC(MONTHS_BETWEEN(SYSDATE, BirthDate) / 12) AS Age
 Select YearsOfService - TRUNC(MONTHS_BETWEEN(SYSDATE, HireDate) / 12) AS YearsOfService
 */