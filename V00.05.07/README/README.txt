
/**@ Project-- GPS CLock

   *@ Team lead  : 

   *@ Developer : Vivek Yadav

	*@ Others : 
----------------------------------------------------------------------------------
   @ Version CC.HH.SS
	-- CC : Company
	-- HH : Hardware
	-- SS : Software

   @ Master :
	-- Take data from GPS
	-- Server NodeMcu will process and Parse data and Find required Time Only.
	-- Then Send that data to Client NodeMcu.
	-- 
	
   @ Slave : 
	-- Take data from Server Or Master
	-- Update RTC
	-- Now read data from RTC
	-- Display On seven Segment
----------------------------------------------------------------------------------

  @ Notifications :
	-- Every funcation should return Something. Try to avoid "void".
	-- All same type funcations should be in different .cpp file with
	   its corresponding .h file.
	-- Comments are neccessary to explain about funcation working.
		Format :
		/*****************************************/
		/*	>>>>	Explain	 <<<<   	 */
		/*	@ purpose of funcation		 */
		/*	@ parametrs if any		 */
		/*	@ return type			 */
		/*****************************************/

	-- Use standard notations while naming funcations.
	-- Funcation name somehow give idea about working.
	-- Always Write debug points or Check points and write comment
	   about all the worries a developer/Tester Should care.
	-- Whenever use macro write commant "// Macro" and decalre it in 
	   headerfile.
----------------------------------------------------------------------------------       
