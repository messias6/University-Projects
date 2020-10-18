-- Q1 Name, NIF and email of student
-- SELECT P.Name, P.NIF, P.email
-- FROM Person P, Student S
-- WHERE P.ID = S.ID and S.student_ID = 'ist112233';

-- Q2 ID, Name, NIF and email of the monitors
-- SELECT distinct M.employee_ID, P.Name, P.NIF, P.email
-- FROM Monitor M, Employee E, Person P
-- WHERE E.ID = P.ID and M.employee_ID = E.employee_ID;

-- Q3 How many computers are available?
-- SELECT pc_ID, location
-- FROM PC
-- WHERE pc_ID NOT IN (SELECT pc_ID FROM use_student WHERE end_time is NULL) 
-- and pc_ID NOT IN (SELECT pc_ID FROM use_employee WHERE end_time is NULL);

-- Q4 Students using a computer right now
-- SELECT S.student_ID, P.Name, PC.pc_ID, PC.location, us.date, us.start_time
-- FROM Student S, Person P, use_student us, PC
-- WHERE PC.pc_ID = us.pc_ID and S.student_ID = us.student_ID and S.ID = P.ID and us.end_time IS NULL;

-- Q5 Who was/is using the PC Nº 3?
-- SELECT S.student_ID, P.Name, us.date, us.start_time, IFNULL(us.end_time, 'Being Used') AS end_time
-- FROM Student S, Person P, use_student us, PC
-- WHERE PC.pc_ID = 3 and us.pc_ID = PC.pc_ID and us.student_ID = S.student_ID and S.ID = P.ID 
-- and us.date BETWEEN (CURRENT_DATE - INTERVAL 30 DAY) and CURRENT_DATE;

-- Q6 Computers assigned by a specific monitor while he was working
-- SELECT  us.date, us.start_time, us.end_time, us.pc_ID, S.student_ID, P.Name
-- FROM Person P, Student S, use_student us, use_employee ue
-- WHERE S.ID = P.ID and us.student_ID = S.student_ID 
-- and us.start_time > ue.start_time and us.start_time < ue.end_time
-- and us.date = ue.date and ue.employee_ID = 'ist440055'
-- ORDER BY date, us.start_time;

-- Q7 Which students have an online account?
-- SELECT S.student_ID, P.Name, h.account_number
-- FROM Student S, Person P, has h
-- WHERE h.student_ID = S.student_ID and S.ID = P.ID;

-- Q8 What has been added as products by the computer technician - Felipe D?
-- SELECT P.product_ID, P.product_name, P.price, R.date
-- FROM Product P, Restock R
-- WHERE R.product_ID = P.product_ID and R.employee_ID = 'ist990099';

-- Q9 What 'insert name' - ist445566 has bought so far in terms of Prints
-- SELECT P.product_name AS Product_Name, SUM(pp.quantity) AS Quantity,SUM(pp.quantity)*P.price AS Final_Price
-- FROM pay_prints pp, has h, Product P
-- WHERE pp.account_number = h.account_number and h.student_ID = 'ist445566' and pp.product_ID = P.product_ID
-- GROUP BY pp.product_ID
-- ORDER BY P.product_name;

-- Q10 What courses 'insert name' - ist445566 is enroll in?
-- SELECT P.product_name AS Courses, P.price as Price
-- FROM pay_courses pc, has h, Product P
-- WHERE pc.account_number = h.account_number and h.student_ID = 'ist445566' and pc.product_ID = P.product_ID;

-- Q11 Available courses that 'insert name' - ist112233 can enroll in
-- SELECT P.product_name, (C.capacity - COUNT(pc.product_ID)) AS Availability, P.price
-- FROM Product P, Courses C
-- LEFT JOIN pay_courses pc ON pc.product_ID = C.product_ID
-- WHERE P.product_ID = C.product_ID 
-- and P.product_ID not in (SELECT pc.product_ID FROM has h, pay_courses pc WHERE h.account_number = pc.account_number and h.student_ID = 'ist112233')
-- GROUP BY P.product_name;

-- Q12 What courses are there and what is the availability and price of each one (similar to the above)
-- SELECT P.product_name AS Courses, (C.capacity - COUNT(pc.product_ID)) AS Availability, P.price AS Price
-- FROM Product P, Courses C
-- LEFT JOIN pay_courses pc ON pc.product_ID = C.product_ID 
-- WHERE P.product_ID = C.product_ID
-- GROUP BY P.product_name
-- ORDER BY P.product_name;

-- Q13 How much has been bought in terms of prints by each person (student)
-- SELECT total.Name, SUM(total.final_price) AS Total_in_Prints
-- FROM 
-- (SELECT Person.Name AS Name, SUM(pp.quantity)*P.price as final_price
-- FROM pay_prints pp, has h, Product P, Person, Student S
-- WHERE pp.account_number = h.account_number and pp.product_ID = P.product_ID and h.student_ID = S.student_ID
-- and S.ID = Person.ID
-- GROUP BY P.product_ID, Person.Name) AS total
-- GROUP BY total.Name;


