<<<<<<< HEAD
const core = require('@actions/core');
=======
>>>>>>> unique_ptr
const github = require('@actions/github');
const postPRInfo = require('./postPRInfo');

async function run() {
    try {
        const context = github.context;

        const response = await postPRInfo(
<<<<<<< HEAD
            core.getInput('webhook'),
=======
>>>>>>> unique_ptr
            context.repo.owner,
            context.repo.repo,
            context.payload.pull_request.number,
            context.runId
        );
    } catch (error) {
        core.setFailed(error.message);
    }
}

run();
