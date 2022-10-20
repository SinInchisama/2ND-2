// online java compiler:
//   https://codechacha.com/ko/java-sorting-array/
//   https://www.onlinegdb.com/

import java.util.Arrays;
import java.util.Comparator;


public class Main {
  public static class City implements Comparable<City> {
    String name; int x, y;
    public City(String name, int x, int y) {
      this.name = name;
      this.x = x;
      this.y = y;
    }
    public String toString() {
      return name+'('+x+','+y+')';
    }
    public int compareTo(City city){
        return this.name.compareTo(city.name);
    }
  }

  static City[] cities = new City[] {
    new City("Links", 1336, 536),    new City("Prosy", 977, 860),
    new City("Rabbi", 6, 758),       new City("Addle", 222, 261),
    new City("Smell", 1494, 836),    new City("Quite", 905, 345),
    new City("Lives", 72, 714),      new City("Cross", 23, 680),
    new City("Synth", 1529, 785),    new City("Tweak", 1046, 426),
    new City("Medic", 1485, 514),    new City("Glade", 660, 476),
    new City("Breve", 1586, 448),    new City("Hotel", 1269, 576),
    new City("Toing", 398, 561),     new City("Scorn", 617, 373),
    new City("Imply", 1253, 403),    new City("Zilch", 1289, 29),
    new City("React", 296, 659),     new City("Fiche", 787, 278),
  };
  public static void main(String args[]) {
    System.out.println(Arrays.toString(cities));
    // sort here by name
    Arrays.sort(cities);
    System.out.println(Arrays.toString(cities));
    // sort here by x coordinate
    Arrays.sort(cities,new Comparator<City>(){
        public int compare(City c1,City c2){
            return c1.x - c2.x;
        }
    });
    System.out.println(Arrays.toString(cities));
  }
}
