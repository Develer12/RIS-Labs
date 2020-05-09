go
use master;
go
Create database RISmain;
Create database RIS1;
Create database RIS2;
go

use RISmain;
go
Create table Watts
(
	id int,
	watt int,
	date datetimeoffset
);
go

use RIS1;
go
Create table Watts
(
	id int,
	watt int,
	date datetimeoffset
);
go

use RIS2;
go
Create table Watts
(
	id int,
	watt int,
	date datetimeoffset
);
go


--datetimeoffset //SYSDATETIMEOFFSET