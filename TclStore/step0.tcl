# How to determine and keep the first 5 smallest items of a list?
# 
# with list in li:
# (1)  As long as the `li` has more than 5 items ...
# (2)      within the first 6 elements ...
# (3)           delete the largest

while {[llength $li] > 5} {
	set mx 0
	for {set i 1} {$i <= 5} {incr i} {	
		if {[lindex $li $mx] < [lindex $li $i]} {
			set mx $i	
		}
	}
	set li [lreplace $li $mx $mx]
}
