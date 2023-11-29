awk '{
 source = $3
 dest = $4
 if (source ~ /^[0-9]+$/ && dest ~ /^[0-9]+$/) {
 sent[source]++
 sent[dest]++
 }
}
END {
 for (node in sent) {
 print "Node " node ": " sent[node] " messages
sent"
 }
}' trace.txt

