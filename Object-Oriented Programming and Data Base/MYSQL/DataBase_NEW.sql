DROP DATABASE IF EXISTS ist181014;
CREATE SCHEMA IF NOT EXISTS ist181014;
USE ist181014;

SET FOREIGN_KEY_CHECKS=0 
;

/* Drop Tables */

DROP TABLE IF EXISTS `Computer_Tech` CASCADE;
DROP TABLE IF EXISTS `Courses` CASCADE;
DROP TABLE IF EXISTS `Employee` CASCADE;
DROP TABLE IF EXISTS `has` CASCADE;
DROP TABLE IF EXISTS `Monitor` CASCADE;
DROP TABLE IF EXISTS `Online_account` CASCADE;
DROP TABLE IF EXISTS `pay_courses` CASCADE;
DROP TABLE IF EXISTS `pay_prints` CASCADE;
DROP TABLE IF EXISTS `PC` CASCADE;
DROP TABLE IF EXISTS `Person` CASCADE;
DROP TABLE IF EXISTS `Prints` CASCADE;
DROP TABLE IF EXISTS `Product` CASCADE;
DROP TABLE IF EXISTS `Restock` CASCADE;
DROP TABLE IF EXISTS `Student` CASCADE;
DROP TABLE IF EXISTS `use_employee` CASCADE;
DROP TABLE IF EXISTS `use_student` CASCADE;

/* Create Tables */

CREATE TABLE `Computer_Tech`
(
	`employee_ID` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_Computer_Tech` PRIMARY KEY (`employee_ID` ASC)
)

;

CREATE TABLE `Courses`
(
	`product_ID` INT NOT NULL,
	`capacity` INT NOT NULL,
	CONSTRAINT `PK_Courses` PRIMARY KEY (`product_ID` ASC)
)

;

CREATE TABLE `Employee`
(
	`employee_ID` VARCHAR(50) NOT NULL,
	`ID` INT NOT NULL,
	CONSTRAINT `PK_Table2` PRIMARY KEY (`employee_ID` ASC)
)

;

CREATE TABLE `has`
(
	`student_ID` VARCHAR(50) NOT NULL,
	`account_number` VARCHAR(50) NOT NULL
)

;

CREATE TABLE `Monitor`
(
	`employee_ID` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_Monitor` PRIMARY KEY (`employee_ID` ASC)
)

;

CREATE TABLE `Online_account`
(
	`account_number` VARCHAR(50) NOT NULL,
	`balance` DOUBLE(10,2) NOT NULL,
	CONSTRAINT `PK_Table2` PRIMARY KEY (`account_number` ASC)
)

;

CREATE TABLE `pay_courses`
(
	`account_number` VARCHAR(50) NOT NULL,
	`product_ID` INT NOT NULL
)

;

CREATE TABLE `pay_prints`
(
	`account_number` VARCHAR(50) NOT NULL,
	`product_ID` INT NOT NULL,
	`quantity` INT NOT NULL
)

;

CREATE TABLE `PC`
(
	`pc_ID` INT NOT NULL,
	`location` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_Table2` PRIMARY KEY (`pc_ID` ASC)
)

;

CREATE TABLE `Person`
(
	`ID` INT NOT NULL,
	`Name` VARCHAR(50) NOT NULL,
	`NIF` INT NOT NULL,
	`email` VARCHAR(50) NOT NULL,
	`password` VARCHAR(50) NOT NULL,
	CONSTRAINT `PK_Person` PRIMARY KEY (`ID` ASC)
)

;

CREATE TABLE `Prints`
(
	`product_ID` INT NOT NULL,
	CONSTRAINT `PK_Prints` PRIMARY KEY (`product_ID` ASC)
)

;

CREATE TABLE `Product`
(
	`product_ID` INT NOT NULL,
	`product_name` VARCHAR(50) NOT NULL,
	`price` DOUBLE(10,2) NOT NULL,
	CONSTRAINT `PK_Table2` PRIMARY KEY (`product_ID` ASC)
)

;

CREATE TABLE `Restock`
(
	`employee_ID` VARCHAR(50) NOT NULL,
	`product_ID` INT NOT NULL,
	`date` DATE NOT NULL
)

;

CREATE TABLE `Student`
(
	`student_ID` VARCHAR(50) NOT NULL,
	`ID` INT NOT NULL,
	CONSTRAINT `PK_Table2` PRIMARY KEY (`student_ID` ASC)
)

;

CREATE TABLE `use_employee`
(
	`pc_ID` INT NOT NULL,
	`employee_ID` VARCHAR(50) NOT NULL,
	`date` DATE NOT NULL,
	`start_time` TIME NOT NULL,
	`end_time` TIME NULL
)

;

CREATE TABLE `use_student`
(
	`pc_ID` INT NOT NULL,
	`student_ID` VARCHAR(50) NOT NULL,
	`date` DATE NOT NULL,
	`start_time` TIME NOT NULL,
	`end_time` TIME NULL
)

;

/* Create Primary Keys, Indexes, Uniques, Checks */

ALTER TABLE `Computer_Tech` 
 ADD INDEX `IXFK_Computer_Tech_Employee` (`employee_ID` ASC);

ALTER TABLE `Courses` 
 ADD INDEX `IXFK_Courses_Product` (`product_ID` ASC);

ALTER TABLE `Employee` 
 ADD INDEX `IXFK_Employee_Person` (`ID` ASC);

ALTER TABLE `has` 
 ADD INDEX `IXFK_has_Online_account` (`account_number` ASC);

ALTER TABLE `has` 
 ADD INDEX `IXFK_has_Student` (`student_ID` ASC);

ALTER TABLE `Monitor` 
 ADD INDEX `IXFK_Monitor_Employee` (`employee_ID` ASC);

ALTER TABLE `pay_courses` 
 ADD INDEX `IXFK_pay_courses_Courses` (`product_ID` ASC);

ALTER TABLE `pay_courses` 
 ADD INDEX `IXFK_pay_courses_Online_account` (`account_number` ASC);

ALTER TABLE `pay_prints` 
 ADD INDEX `IXFK_pay_prints_Online_account` (`account_number` ASC);

ALTER TABLE `pay_prints` 
 ADD INDEX `IXFK_pay_prints_Prints` (`product_ID` ASC);

ALTER TABLE `Prints` 
 ADD INDEX `IXFK_Prints_Product` (`product_ID` ASC);

ALTER TABLE `Restock` 
 ADD INDEX `IXFK_Restock_Computer_Tech` (`employee_ID` ASC);

ALTER TABLE `Restock` 
 ADD INDEX `IXFK_Restock_Product` (`product_ID` ASC);

ALTER TABLE `Student` 
 ADD INDEX `IXFK_Student_Person` (`ID` ASC);

ALTER TABLE `use_employee` 
 ADD INDEX `IXFK_use_employee_Employee` (`employee_ID` ASC);

ALTER TABLE `use_employee` 
 ADD INDEX `IXFK_use_employee_PC` (`pc_ID` ASC);

ALTER TABLE `use_student` 
 ADD INDEX `IXFK_use_student_PC` (`pc_ID` ASC);

ALTER TABLE `use_student` 
 ADD INDEX `IXFK_use_student_Student` (`student_ID` ASC);

/* Create Foreign Key Constraints */

ALTER TABLE `Computer_Tech` 
 ADD CONSTRAINT `FK_Computer_Tech_Employee`
	FOREIGN KEY (`employee_ID`) REFERENCES `Employee` (`employee_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Courses` 
 ADD CONSTRAINT `FK_Courses_Product`
	FOREIGN KEY (`product_ID`) REFERENCES `Product` (`product_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Employee` 
 ADD CONSTRAINT `FK_Employee_Person`
	FOREIGN KEY (`ID`) REFERENCES `Person` (`ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `has` 
 ADD CONSTRAINT `FK_has_Online_account`
	FOREIGN KEY (`account_number`) REFERENCES `Online_account` (`account_number`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `has` 
 ADD CONSTRAINT `FK_has_Student`
	FOREIGN KEY (`student_ID`) REFERENCES `Student` (`student_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Monitor` 
 ADD CONSTRAINT `FK_Monitor_Employee`
	FOREIGN KEY (`employee_ID`) REFERENCES `Employee` (`employee_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `pay_courses` 
 ADD CONSTRAINT `FK_pay_courses_Courses`
	FOREIGN KEY (`product_ID`) REFERENCES `Courses` (`product_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `pay_courses` 
 ADD CONSTRAINT `FK_pay_courses_Online_account`
	FOREIGN KEY (`account_number`) REFERENCES `Online_account` (`account_number`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `pay_prints` 
 ADD CONSTRAINT `FK_pay_prints_Online_account`
	FOREIGN KEY (`account_number`) REFERENCES `Online_account` (`account_number`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `pay_prints` 
 ADD CONSTRAINT `FK_pay_prints_Prints`
	FOREIGN KEY (`product_ID`) REFERENCES `Prints` (`product_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Prints` 
 ADD CONSTRAINT `FK_Prints_Product`
	FOREIGN KEY (`product_ID`) REFERENCES `Product` (`product_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Restock` 
 ADD CONSTRAINT `FK_Restock_Computer_Tech`
	FOREIGN KEY (`employee_ID`) REFERENCES `Computer_Tech` (`employee_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Restock` 
 ADD CONSTRAINT `FK_Restock_Product`
	FOREIGN KEY (`product_ID`) REFERENCES `Product` (`product_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `Student` 
 ADD CONSTRAINT `FK_Student_Person`
	FOREIGN KEY (`ID`) REFERENCES `Person` (`ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `use_employee` 
 ADD CONSTRAINT `FK_use_employee_Employee`
	FOREIGN KEY (`employee_ID`) REFERENCES `Employee` (`employee_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `use_employee` 
 ADD CONSTRAINT `FK_use_employee_PC`
	FOREIGN KEY (`pc_ID`) REFERENCES `PC` (`pc_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `use_student` 
 ADD CONSTRAINT `FK_use_student_PC`
	FOREIGN KEY (`pc_ID`) REFERENCES `PC` (`pc_ID`) ON DELETE Restrict ON UPDATE Restrict;

ALTER TABLE `use_student` 
 ADD CONSTRAINT `FK_use_student_Student`
	FOREIGN KEY (`student_ID`) REFERENCES `Student` (`student_ID`) ON DELETE Restrict ON UPDATE Restrict;

SET FOREIGN_KEY_CHECKS=1 ;

-- PERSON
INSERT INTO Person VALUES
-- Student
	('112233','Baran Wilks','111222333','baran.wilks@gmail.com','11Baran22Wilks33'),
	('223344','Jannat Timms','222333444','jannat.timms@gmail.com','22Jannat33Timms44'),
	('334455','Agata Frank','333444555','agata.frank@gmail.com','123'),  -- USED FOR TESTING (WITH NO online account)
	('445566','Celia Fountain','444555666','celia.f@gmail.com','123'), -- USED FOR TESTING (with online account)
	('556677','Farzana Andersen','555666777','farzana.andersen@gmail.com','55Farzana66Andersen77'),
	('667788','Sonia Sheehan','666777888','sonia.sheehan@gmail.com','66Sonia77Sheehan88'),
	('778899','Dexter Dunn','777888999','dexter.dunn@gmail.com','77Dexter88Dunn99'),
	('889910','Carolyn Palmer','888999100','carolyn.palmer@gmail.com','88Carolyn99Palmer10'),
	('991011','Bella Whitfield','999100110','bella.whitfield@gmail.com','99Bella10Whitfield11'),
	('101112','Huzaifa Carney','100110120','huzaifa.carney@gmail.com','10Huzaifa11Carney12'),
-- Monitor
	('110022','Will Hays','111000222','will.hays@gmail.com','123'), -- USED FOR TESTING (monitor)
	('440055','Steven Campbell','444000555','steven.campbell@gmail.com','44Steven00Campbell55'),
	('880099','Tyson Phan','888000999','tyson.phan@gmail.com','88Tyson00Phan99'),
-- Computer_tech
	('990099','Felipe D','999000999','felipe.d@gmail.com','123'); -- USED FOR TESTING (comp tech)

-- STUDENT 
INSERT INTO Student VALUES 
	('ist112233','112233'),
	('ist223344','223344'),
	('ist334455','334455'),
	('ist445566','445566'),
	('ist556677','556677'),
	('ist667788','667788'),
	('ist778899','778899'),
	('ist889910','889910'),
	('ist991011','991011'),
	('ist101112','101112');

-- EMPLOYEE
INSERT INTO Employee VALUES 
	('ist110022','110022'),
	('ist440055','440055'),
	('ist880099','880099'),
	('ist990099','990099');
-- Monitor
INSERT INTO Monitor VALUES
	('ist110022'),
	('ist440055'),
	('ist880099');
-- Computer Technician
INSERT INTO Computer_Tech VALUES ('ist990099');

-- PC
INSERT INTO PC VALUES 
	(1,'LEMAC'),
	(2,'LEMAC'),
	(3,'LEMAC'),
	(4,'LTI'),
	(5,'LEMAC'),
	(6,'LEMAC'),
	(7,'LEMAC'),
	(8,'LTI'),
	(9,'LTI'),
	(10,'LTI'),
    (99,'LEMAC');

-- PRODUCT
INSERT INTO Product VALUES 
	(1,'A4 - Front',0.03),
	(2,'A4 - Front and Back',0.04),
	(3,'A4 - Front - Colour',0.160),
	(4,'A4 - Front and Back - Colour',0.270),	
	(5,'A3 - Front',0.05),
	(6,'A3 - Front and Back',0.08),
	(7,'A3 - Front - Colour',0.23),
	(8,'A3 - Front and Back - Colour',0.4),
	(9,'Scanning - A4',0.02),
	(10,'Scanning - A3',0.04),
	(11,'Python',30),
	(12,'Structural Mechanics',30),
	(13,'Computational Mechanics',30),
	(14,'Matlab',30);
    
-- Prints
INSERT INTO Prints VALUES 
	(1),
	(2),
	(3),
	(4),	
	(5),
	(6),
	(7),
	(8),
	(9),
	(10);
-- Courses (ID and capacity of each course)
INSERT INTO Courses VALUES 
	(11,15),
	(12,15),
	(13,15),
	(14,15);

-- ONLINE ACCOUNT (account number and balance)
INSERT INTO Online_account VALUES 
	('PT29524192157725574171151',3.20),
	('PT71785678906197281660186',5.00),
	('PT82079251492890212139929',0.20),
	('PT29024192656565666171151',0.45),
	('PT05187515229051210277177',4.15),
	('PT46608308083106014045395',1.47);
    
-- HAS
INSERT INTO has VALUES 
	('ist112233','PT05187515229051210277177'),
	('ist445566','PT82079251492890212139929'),
	('ist101112','PT46608308083106014045395'),
	('ist889910','PT29024192656565666171151'),
	('ist778899','PT71785678906197281660186'),
	('ist223344','PT29524192157725574171151');

-- Pay Prints
INSERT INTO pay_prints VALUES 
	('PT29524192157725574171151',3,10),
	('PT82079251492890212139929',5,3),
	('PT71785678906197281660186',9,10);

-- Pay Courses
INSERT INTO pay_courses VALUES
	('PT05187515229051210277177',11),
	('PT46608308083106014045395',11),
	('PT29024192656565666171151',14),
    ('PT82079251492890212139929',11);

-- RESTOCK
INSERT INTO Restock VALUES ('ist990099',13,'2018-12-12');

-- Use Employee
INSERT INTO use_employee VALUES 
	(99,'ist440055','2018-10-02','09:30:01','11:55:30'),
	(99,'ist110022','2018-12-21','12:00:12','17:55:30'),
	(99,'ist440055','2019-01-08','08:00:00','13:30:00');

-- Use Student
INSERT INTO use_student VALUES 
	(3,'ist112233','2018-12-21','13:12:30','17:55:00'),
	(9,'ist991011','2019-01-07','11:30:12','18:55:00'),
	(7,'ist778899','2019-01-08','09:35:30',NULL),
	(5,'ist112233','2019-06-15','23:37:34',NULL);