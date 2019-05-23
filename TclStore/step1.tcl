proc n_extremes {li {n 5} args} {
	# args are for `lsort`-style sorting options
	# they are not yet implemented
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
