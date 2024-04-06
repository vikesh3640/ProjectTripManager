function startExpenseSplitter() {
    var numPeople = parseInt(document.getElementById("numPeople").value);
    var spend = new Array(numPeople).fill(0);
    var actualExp = new Array(numPeople).fill(0);
    var peopleNames = [];

    // Prompt user for names of people
    for (var i = 0; i < numPeople; i++) {
        var name = prompt("Enter name for person " + (i+1) + ":");
        peopleNames.push(name);
    }

    var over = false;
    while (!over) {
        var Sno = parseInt(prompt("Enter Sno of payer for current transaction(1,2..N):")) - 1;
        var amt = parseInt(prompt("Enter amount paid by payer:"));
        spend[Sno] += amt;
        var np = parseInt(prompt("Enter the number of people in which the bill is split:"));
        var arr = [];
        for (var k = 0; k < np; k++) {
            var personIndex = parseInt(prompt("Enter person number:")) - 1;
            arr.push(personIndex);
        }
        var contro = amt / np;
        for (var k = 0; k < np; k++) {
            actualExp[arr[k]] += contro;
        }
        over = confirm("Is trip over? Click OK if yes, Cancel if no.");
    }

    var due = new Array(numPeople);
    for (var j = 0; j < numPeople; j++) {
        due[j] = spend[j] - actualExp[j];
    }

    var size = numPeople;
    var array = [];
    for (var i = 0; i < size; ++i) {
        array.push({ serial: i, value: due[i] });
    }

    array.sort(function(a, b) {
        return a.value - b.value;
    });

    var negc = 0;
    for (var i = 0; i < size; i++) {
        if (array[i].value < 0) {
            negc++;
        } else {
            break;
        }
    }

    var outputHTML = "<h2>Expense Summary</h2><ul>";
    var end = size - 1;
    for (var j = 0; j < negc; j++) {
        if (-array[j].value > array[end].value) {
            if (Math.round(array[end].value) !== 0) {
                outputHTML += "<li>" + peopleNames[array[j].serial] + " should give " + Math.round(array[end].value) + " Rs to " + peopleNames[array[end].serial] + "</li>";
            }
            array[j].value += array[end].value;
            array[end].value = 0;
            end--;
            j--;
        } else if (-array[j].value < array[end].value) {
            if (Math.round(-array[j].value) !== 0) {
                outputHTML += "<li>" + peopleNames[array[j].serial] + " should give " + Math.round(-array[j].value) + " Rs to " + peopleNames[array[end].serial] + "</li>";
            }
            array[end].value += array[j].value;
            array[j].value = 0;
        } else if (-array[j].value === array[end].value) {  
            if (Math.round(-array[j].value) !== 0) {
                outputHTML += "<li>" + peopleNames[array[j].serial] + " should give " + Math.round(-array[j].value) + " Rs to " + peopleNames[array[end].serial] + "</li>";
            }
            array[j].value = 0;
            array[end].value = 0;
            end--;
        }
    }
    outputHTML += "</ul>";
    document.getElementById("output").innerHTML = outputHTML;
}
