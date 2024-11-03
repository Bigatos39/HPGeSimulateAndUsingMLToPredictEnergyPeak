import os

import numpy as np
import pandas as pd
import ROOT as rt


# ----------------------------------------------------------------- //
# ---------------- PRE PROCESSING from ROOT FILE ------------------ //
# ----------------------------------------------------------------- //
class ProcessDataFromRootFile:
    def __init__(self, file_paths, tree_name="HPGe", branch_name="fEdep"):
        self.file_paths = file_paths
        self.tree_name = tree_name
        self.branch_name = branch_name

    # open file
    def _open_file(self, file_path):
        file = rt.TFile.Open(file_path)
        if not file or file.IsZombie():
            raise ValueError(f"Could not open file {file_path}")

        tree = file.Get(self.tree_name)
        if not tree:
            file.Close()
            raise ValueError(f"Tree {self.tree_name} not found")
        return file, tree

    def load_all_data(self):
        all_data = pd.DataFrame({self.branch_name: [], "Energy": []})

        for file_path in self.file_paths:
            file = None
            try:
                file, tree = self._open_file(file_path)
                energy_level = self.extract_energy_level(file_path)

                data = {self.branch_name: []}
                for entry in tree:
                    data[self.branch_name].append(getattr(entry, self.branch_name))

                data_df = pd.DataFrame(data)
                data_df["Energy"] = energy_level
                all_data = pd.concat([all_data, data_df], ignore_index=True)
            finally:
                if file:
                    file.Close()

        return all_data

    def extract_energy_level(self, file_path):
        base_name = os.path.basename(file_path)
        energy_level = int(base_name.replace("output", "").replace(".root", ""))
        return energy_level


from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split


# ----------------------------------------------------------------- //
# ------------------------ RANDOM FOREST -------------------------- //
# ----------------------------------------------------------------- //
class RandomForestModel:
    def __init__(self, n_estimators=500, test_size=0.2, random_state=42):
        self.n_estimators = n_estimators
        self.test_size = test_size
        self.random_state = random_state
        self.model = RandomForestRegressor(
            n_estimators=self.n_estimators, random_state=self.random_state
        )
        self.X_train = None
        self.X_test = None
        self.y_train = None
        self.y_test = None

    def prepare_data(self, data):
        X = data[["fEdep"]]
        y = data["Energy"]
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(
            X, y, test_size=self.test_size, random_state=self.random_state
        )

    def train(self):
        self.model.fit(self.X_train, self.y_train)

    def predict(self):
        return self.model.predict(self.X_test)

    def evaluate(self):
        y_pred = self.predict()
        mse = mean_squared_error(self.y_test, y_pred)
        print(f"Mean Squared Error: {mse:.4f}")

        return mse


# ----------------------------------------------------------------- //
# ---------------------------- MAIN ------------------------------- //
# ----------------------------------------------------------------- //
def main():
    file_directory = input("Enter your path to data directory: ")
    num_files = int(input("Enter number of your files: "))
    file_paths = [
        os.path.join(file_directory, f"output{i}.root")
        for i in range(650, num_files + 650)
    ]

    analyzer = ProcessDataFromRootFile(file_paths)
    all_data = analyzer.load_all_data()

    # testing
    # print(all_data.head())
    # print(f"All events: {len(all_data)}")

    model = RandomForestModel(n_estimators=100, test_size=0.2, random_state=42)
    model.prepare_data(all_data)
    model.train()
    model.evaluate()


if __name__ == "__main__":
    main()
