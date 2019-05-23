proc n_extremes {li {n 5} args} {

	# Summary: Keep `n` extreme values from a list

	# Argument Usage:
	# li      : the input list
        # [n = 5] : elements to keep

	# Return Value:
        # TCL_OK is returned with the (shortened) list as result

	# Categories: xilinxtclstore, projutils

	while {[llength $li] > $n} {
		set mx 0
		for {set i 1} {$i <= $n} {incr i} {	
			if {[lindex $li $mx] < [lindex $li $i]} {
				set mx $i	
			}
		}
		set li [lreplace $li $mx $mx]
	}
	return $li
}

if 1 {
	foreach {    li     n  expected} {
	      # ----------- - ----------
		{1 2 3 4 5} 5 {1 2 3 4 5}
		{1 2 3 4 5} 3 {1 2 3}
		{5 4 3 2 1} 3 {3 2 1}
		{1 2 1 2}   2 {1 1}
		{}          2 {}
	} {
		set result [n_extremes $li $n]
		if {![string equal $result $expected]} {
			puts "`n_extremes` failed for: {$li} $n -> {$expected}"
			incr failed
		}
	}
	if {[info exists failed]} {
		error "`n_extremes` failed in $failed tests"
	}
	puts "`n_expected` passed all tests ***"
}
