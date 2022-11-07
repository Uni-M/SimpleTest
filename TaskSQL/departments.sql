CREATE TABLE IF NOT EXISTS departments
(
    dept_id     bigint primary key,
    dept_name   varchar unique
);
CREATE INDEX IF NOT EXISTS departments_idx ON departments (dept_id);

CREATE TABLE IF NOT EXISTS employers
(
	emp_id		bigint primary key,
	emp_name	varchar, 
	dept_id		bigint REFERENCES departments ON DELETE restrict ON UPDATE cascade,
	birth_date	date
);
CREATE INDEX IF NOT EXISTS employers_idx ON employers (emp_id);

CREATE TABLE IF NOT EXISTS contacts
(
	emp_id		bigint primary key REFERENCES employers ON DELETE restrict ON UPDATE cascade,
	cont_type	char,
	cont_text	varchar
);
CREATE INDEX IF NOT EXISTS contacts_idx ON contacts (emp_id);

INSERT INTO departments (dept_id, dept_name)
VALUES (1, 'department 1');
INSERT INTO departments (dept_id, dept_name)
VALUES (2, 'department 2');
INSERT INTO departments (dept_id, dept_name)
VALUES (3, 'department 3');

INSERT INTO employers (emp_id, emp_name, dept_id, birth_date)
VALUES (1, 'Anna', 1, '1992-04-24');
INSERT INTO employers (emp_id, emp_name, dept_id, birth_date)
VALUES (2, 'Olga', 2, '1990-11-11');
INSERT INTO employers (emp_id, emp_name, dept_id, birth_date)
VALUES (3, 'Slava', 1, '1992-08-15');


INSERT INTO contacts (emp_id, cont_type, cont_text)
VALUES (1, 'e', 'cont_text1');
INSERT INTO contacts (emp_id, cont_type, cont_text)
VALUES (2, 'm', 'cont_text2');
INSERT INTO contacts (emp_id, cont_type, cont_text)
VALUES (3, 'p', 'cont_text2');



(
	SELECT d.dept_name as Поле, ' ' as Значение 
	FROM departments d ORDER BY d.dept_id
)
UNION
(
	SELECT e.emp_name, c.cont_text FROM employers e
	JOIN contacts c ON e.emp_id = c.emp_id
)